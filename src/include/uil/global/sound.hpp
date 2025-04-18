//
// Purpur Tentakel
// 17.04.25
//

#pragma once
#include <unordered_map>
#include <cpt/types.hpp>
#include <vector>
#include <filesystem>

namespace uil {
    template<typename T>
    concept IsSoundFile = std::is_same_v<T, Sound> or std::is_same_v<T, Music>;

    class SoundManager final {
    public:
        enum Result {
            InvalidPath,

            UnknownLevelID,
            UnknownSoundID,
            UnknownMusicCollectionID,

            Success,
        };

        [[nodiscard]] static bool is_success(Result result);

    private:
        struct SoundEntry final {
            std::vector<Sound> sound{};
            cpt::usize level_id{ 0 };
            bool m_muted{ false };
        };

        struct MusicEntry final {
            std::vector<Music> music{};
            cpt::usize level_id{ 0 };
            bool m_muted{ false };
        };

        std::unordered_map<cpt::usize, float> m_levels{};
        std::unordered_map<cpt::usize, SoundEntry> m_sounds{};
        std::unordered_map<cpt::usize, MusicEntry> m_music_collections{};
        MusicEntry m_current_music_collection{ std::vector<Music>{} };
        float m_main_level{ 1.0f };

        template<IsSoundFile T>
        Result set_level_ray(T const& file, cpt::usize const level_id) {
            if (not m_levels.contains(level_id)) {
                return UnknownLevelID;
            }

            auto const level = m_levels.at(level_id) * m_main_level;

            if constexpr (std::is_same_v<T, Sound>) {
                SetSoundVolume(file, level);
                return Success;
            }
            if constexpr (std::is_same_v<T, Music>) {
                SetMusicVolume(file, level);
                return Success;
            }
        }

    public:
        SoundManager();
        SoundManager(SoundManager const&)            = delete;
        SoundManager(SoundManager&&)                 = delete;
        SoundManager& operator=(SoundManager const&) = delete;
        SoundManager& operator=(SoundManager&&)      = delete;
        ~SoundManager();

        Result load_sound(cpt::usize& id, std::filesystem::path const& path, cpt::usize alias_pre_load_count = 0);
        Result link_sound_to_level(cpt::usize sound_id, cpt::usize level_id);
        Result play_sound(cpt::usize id);
        /**
         *
         * @param id id of the sound (or alias) to check
         * @return returns if the sound or at least one of its aliasses is currently playing.
         */
        [[nodiscard]] bool is_sound_playing(cpt::usize id) const;

        /*
        [[nodiscard]] cpt::usize try_load_music_collection(std::vector<std::string> const& paths);
        [[nodiscard]] bool link_music_collection_to_level(cpt::usize sound_id, cpt::usize level_id);
        void play_music_collection(cpt::usize music);
        */

        void set_level(cpt::usize level_id, float level);
    };
}
