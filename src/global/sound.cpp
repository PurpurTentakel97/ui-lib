//
// Purpur Tentakel
// 17.04.25
//

#include <algorithm>
#include <ranges>
#include <raylib.h>
#include <uil/global/sound.hpp>
#include <uil/helper/path.hpp>

namespace uil {
    bool SoundManager::is_success(Result const result) {
        return result == Success;
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

    SoundManager::Result SoundManager::load_sound(cpt::usize& id,
                                                  std::filesystem::path const& path,
                                                  cpt::usize const alias_pre_load_count) {
        auto const sound = LoadSound(make_absolute_path(path).string().c_str());
        if (not IsSoundValid(sound)) {
            return InvalidPath;
        }

        id = cpt::usize{ m_sounds.size() + 1 };
        m_sounds.insert({ id, SoundEntry{ std::vector{ sound } } });
        for (cpt::usize i = 0; i < alias_pre_load_count; ++i) {
            m_sounds[id].sound.push_back(LoadSoundAlias(sound));
        }
        return Success;
    }

    SoundManager::Result SoundManager::link_sound_to_level(cpt::usize const sound_id, cpt::usize const level_id) {
        if (not m_levels.contains(level_id)) {
            return UnknownLevelID;
        }

        if (not m_sounds.contains(sound_id)) {
            return UnknownSoundID;
        }

        m_sounds[sound_id].level_id = level_id;
        return Success;
    }

    SoundManager::Result SoundManager::play_sound(cpt::usize const id) {
        if (not m_sounds.contains(id)) {
            return UnknownSoundID;
        }

        auto& sounds = m_sounds[id];

        for (auto const& sound : sounds.sound) {
            if (IsSoundPlaying(sound)) {
                continue;
            }
            set_level_ray(sound, sounds.level_id);
            PlaySound(sound);
            return Success;
        }

        auto const alias = LoadSoundAlias(sounds.sound[0]);
        sounds.sound.push_back(alias);
        set_level_ray(alias, sounds.level_id);
        PlaySound(alias);
        return Success;
    }

    void SoundManager::set_level(cpt::usize const level_id, float const level) {
        if (level_id == 0) {
            m_main_level = level;
            return;
        }

        if (m_levels.contains(level_id)) {
            m_levels[level_id] = level;
            return;
        }

        m_levels.insert({ level_id, level });
    }
}
