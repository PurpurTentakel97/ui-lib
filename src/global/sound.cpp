//
// Purpur Tentakel
// 17.04.25
//

#include <algorithm>
#include <cpt/log.hpp>
#include <ranges>
#include <raylib.h>
#include <uil/global/sound.hpp>
#include <cpt/files.hpp>

namespace uil {
    bool SoundManager::is_success(Result const result) {
        return result == Result::Success;
    }

    SoundManager::LevelEntry& SoundManager::main_level() {
        return m_levels.at(0);
    }

    bool SoundManager::is_main_level(cpt::usize const level_id) {
        return level_id == 0;
    }

    void SoundManager::update_current_music_level(cpt::usize const level_id) {
        if (not m_levels.contains(level_id)) { return; }
        if (not m_current_music) { return; }
        if (not m_current_music_collection) { return; }
        if (m_current_music_collection.value()->level_id != level_id) { return; }

        set_level_ray(*m_current_music.value(), m_current_music_collection.value()->level_id);
    }

    void SoundManager::update_current_music_collection() {
        if (not m_current_music_collection) { return; }
        if (not is_music_playing() && not m_is_music_paused) {
            if (m_next_music_index >= m_current_music_collection.value()->music.size()) {
                m_next_music_index = 0;
            }
            m_current_music = &m_current_music_collection.value()->music[m_next_music_index];
            set_level_ray(*m_current_music.value(), m_current_music_collection.value()->level_id);
            PlayMusicStream(*m_current_music.value());
            cpt::log::info("next background music");

            ++m_next_music_index;
        }

        if (m_current_music.has_value() and is_music_playing()) {
            UpdateMusicStream(*m_current_music.value());
        }
    }

    SoundManager::SoundManager() {
        InitAudioDevice();
    }

    SoundManager::~SoundManager() {
        for (const auto& sounds : m_sounds | std::views::values) {
            if (sounds.sound.empty()) { continue; }
            if (sounds.sound.size() > 1) {
                std::ranges::for_each(sounds.sound.begin() + 1, sounds.sound.end(), UnloadSoundAlias);
            }
            UnloadSound(sounds.sound[0]);
        }

        std::ranges::for_each(m_music_collections,
                              [](auto const& music_collection) {
                                  std::ranges::for_each(music_collection.second.music, UnloadMusicStream);
                              });

        CloseAudioDevice();
    }

    // global -------------------------------------------
    void SoundManager::set_level(cpt::usize const id, float const level) {
        if (not m_levels.contains(id)) {
            m_levels.insert({ id, { level } });
            return;
        }

        m_levels[id].value = level;
        update_current_music_level(id);
    }

    float SoundManager::get_level(cpt::usize const id) const {
        if (not m_levels.contains(id)) {
            return 0.0f;
        }

        return m_levels.at(id).value;
    }

    SoundManager::Result SoundManager::toggle_mute_sound_level(cpt::usize const id) {
        if (not m_levels.contains(id)) { return Result::UnknownLevelID; }
        m_levels[id].muted = not m_levels[id].muted;
        update_current_music_level(id);
        return Result::Success;
    }

    SoundManager::Result SoundManager::set_mute_sound_level(cpt::usize const id, bool const is_mute) {
        if (not m_levels.contains(id)) { return Result::UnknownLevelID; }
        m_levels[id].muted = is_mute;
        update_current_music_level(id);
        return Result::Success;
    }

    bool SoundManager::is_sound_level_muted(cpt::usize const id) const {
        if (not m_levels.contains(id)) { return false; }
        return m_levels.at(id).muted;
    }

    void SoundManager::update() {
        update_current_music_collection();
    }

    // sound --------------------------------------------------
    tl::expected<cpt::usize, SoundManager::Result> SoundManager::load_sound(std::filesystem::path const& path,
                                                                            cpt::usize const alias_pre_load_count) {
        auto const sound = LoadSound(cpt::make_absolute_path(path).string().c_str());
        if (not IsSoundValid(sound)) {
            return tl::unexpected{ Result::InvalidPath };
        }

        auto const id = cpt::usize{ m_sounds.size() + 1 };
        m_sounds.insert({ id, SoundEntry{ std::vector{ sound } } });
        for (cpt::usize i = 0; i < alias_pre_load_count; ++i) {
            m_sounds[id].sound.push_back(LoadSoundAlias(sound));
        }
        return id;
    }

    SoundManager::Result SoundManager::link_sound_to_level(cpt::usize const sound_id, cpt::usize const level_id) {
        if (not m_levels.contains(level_id)) {
            return Result::UnknownLevelID;
        }

        if (not m_sounds.contains(sound_id)) {
            return Result::UnknownSoundID;
        }

        m_sounds[sound_id].level_id = level_id;
        return Result::Success;
    }

    SoundManager::Result SoundManager::play_sound(cpt::usize const id) {
        if (not m_sounds.contains(id)) {
            return Result::UnknownSoundID;
        }

        auto& sounds = m_sounds[id];

        for (auto const& sound : sounds.sound) {
            if (IsSoundPlaying(sound)) {
                continue;
            }
            set_level_ray(sound, sounds.level_id);
            PlaySound(sound);
            return Result::Success;
        }

        auto const alias = LoadSoundAlias(sounds.sound[0]);
        sounds.sound.push_back(alias);
        set_level_ray(alias, sounds.level_id);
        PlaySound(alias);
        return Result::Success;
    }

    bool SoundManager::is_sound_playing(cpt::usize const id) const {
        if (not m_sounds.contains(id)) {
            return false;
        }
        return std::ranges::any_of(m_sounds.at(id).sound,
                                   [](auto const& sound) {
                                       return IsSoundPlaying(sound);
                                   });
    }

    // music ----------------------------------------
    tl::expected<cpt::usize, SoundManager::Result> SoundManager::load_music_collection(
            std::vector<std::filesystem::path> const& path) {
        if (path.empty()) {
            return tl::unexpected{ Result::EmptyContainer };
        }

        auto result           = Result::Success;
        auto music_collection = MusicEntry{};
        for (auto const& p : path) {
            auto music = LoadMusicStream(cpt::make_absolute_path(p).string().c_str());
            if (not IsMusicValid(music)) {
                result = Result::InvalidPath;
                continue;
            }

            music.looping = false;
            music_collection.music.push_back(music);
        }

        if (music_collection.music.empty()) {
            return tl::unexpected{ Result::InvalidPath };
        }

        auto const id = m_music_collections.size() + 1;
        m_music_collections.insert({ id, std::move(music_collection) });

        if (not is_success(result)) {
            return tl::unexpected{ result };
        }

        return id;
    }

    SoundManager::Result SoundManager::link_music_collection_to_level(cpt::usize const music_collection_id,
                                                                      cpt::usize const level_id) {
        if (not m_music_collections.contains(music_collection_id)) { return Result::UnknownMusicCollectionID; }
        if (not m_levels.contains(level_id)) { return Result::UnknownLevelID; }

        m_music_collections[music_collection_id].level_id = level_id;
        return Result::Success;
    }

    SoundManager::Result SoundManager::start_music_collection(cpt::usize const id) {
        if (is_music_playing()) { return Result::StillMusicPlaying; }
        if (not m_music_collections.contains(id)) { return Result::UnknownMusicCollectionID; }
        m_current_music_collection = &m_music_collections.at(id);
        m_is_music_paused          = false;
        m_next_music_index         = 0;

        update_current_music_collection();

        return Result::Success;
    }

    SoundManager::Result SoundManager::pause_music_collection() {
        if (not is_music_playing()) { return Result::NoMusicPlaying; }
        m_is_music_paused = true;
        PauseMusicStream(*m_current_music.value());
        return Result::Success;
    }

    SoundManager::Result SoundManager::resume_music_collection() {
        if (is_music_playing()) { return Result::StillMusicPlaying; }
        if (not m_current_music) { return Result::NoCurrentMusic; }
        m_is_music_paused = false;
        ResumeMusicStream(*m_current_music.value());
        return Result::Success;
    }

    SoundManager::Result SoundManager::stop_music_collection() {
        if (not is_music_playing()) { return Result::NoMusicPlaying; }
        if (not m_current_music) { return Result::NoCurrentMusic; }
        StopMusicStream(*m_current_music.value());
        m_current_music            = {};
        m_current_music_collection = {};
        m_is_music_paused          = false;
        return Result::Success;
    }

    SoundManager::Result SoundManager::switch_music_collection(cpt::usize const id) {
        if (not m_music_collections.contains(id)) { return Result::UnknownMusicCollectionID; }
        if (m_current_music) {
            StopMusicStream(*m_current_music.value());
            m_current_music = {};
        }

        m_current_music_collection = &m_music_collections.at(id);
        m_is_music_paused          = false;
        update_current_music_collection();
        return Result::Success;
    }

    bool SoundManager::is_music_collection_playing(cpt::usize const id) const {
        if (not m_music_collections.contains(id)) { return false; }
        return std::ranges::any_of(m_music_collections.at(id).music,
                                   [](auto const& music) {
                                       return IsMusicStreamPlaying(music);
                                   });
    }

    bool SoundManager::is_music_playing() const {
        if (not m_current_music.has_value()) { return false; }
        return IsMusicStreamPlaying(*m_current_music.value());
    }
}
