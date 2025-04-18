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
        enum class Result {
            InvalidPath,

            UnknownLevelID,
            UnknownSoundID,
            UnknownMusicCollectionID,

            Success,
        };

        enum class Fade {
            Default,

            In,
            Out,
            InOut,
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
        float m_main_level{ 1.0f };
        float m_fade_per_second{ 1.0f };

        std::unordered_map<cpt::usize, SoundEntry> m_sounds{};

        std::unordered_map<cpt::usize, MusicEntry> m_music_collections{};
        MusicEntry m_current_music_collection{ std::vector<Music>{} };
        MusicEntry m_next_music_collection{ std::vector<Music>{} };
        Music m_current_music{};

        template<IsSoundFile T>
        Result set_level_ray(T const& file, cpt::usize const level_id) {
            if (not m_levels.contains(level_id)) {
                return Result::UnknownLevelID;
            }

            auto const level = m_levels.at(level_id) * m_main_level;

            if constexpr (std::is_same_v<T, Sound>) {
                SetSoundVolume(file, level);
                return Result::Success;
            }
            if constexpr (std::is_same_v<T, Music>) {
                SetMusicVolume(file, level);
                return Result::Success;
            }
        }

    public:
        SoundManager();
        SoundManager(SoundManager const&)            = delete;
        SoundManager(SoundManager&&)                 = delete;
        SoundManager& operator=(SoundManager const&) = delete;
        SoundManager& operator=(SoundManager&&)      = delete;
        ~SoundManager();

        // global ---------------------------------------
        /**
         * call this to add a new level id by just providing an unknown id here.
         * call this with id 0 to set the global level
         *
         * @param level_id id of the level to set (0 is the global level)
         * @param level amount that the level gets set to. 0.0f - 1.0f
         */
        void set_level(cpt::usize level_id, float level);

        /**
         * call it with id 0 to get the main level.
         * it returns 0 when the id is not existing.
         *
         * @param level_id id of the level to get
         * @return returns the value of the provided level; 0 == main level
         */
        [[nodiscard]] float get_level(cpt::usize level_id) const;


        /**
         *
         * @param fade_per_second amount that the volume is faded in one second until the maximum volume is reached
         */
        void set_fade_per_second(float fade_per_second);

        /**
         *
         * @return the amount that the volume is faded in one second
         */
        [[nodiscard]] float get_fade_per_second() const;

        /**
         * updates the music streams and fades.
         */
        void update();

        // sound ------------------------------------------
        /**
         *
         * @param id OUT provides / returns the new id of the loaded sound and its aliases
         * @param path provides the path of the loaded sound. Can be a relative or an absolute path. A relative Path will be called with the working directory
         * @param alias_pre_load_count loads an initial amound of aliases. Use this if sounds should overlap
         * @return if the sound is successfully loaded
         */
        Result load_sound(cpt::usize& id, std::filesystem::path const& path, cpt::usize alias_pre_load_count = 0);
        /**
         * you need to add the sound and set the soundlevel first to make sure both ids are present.
         *
         * @param sound_id id of the to link sound
         * @param level_id id of the level the sound gets linked to
         * @return returns if the linkage was successfully
         */
        Result link_sound_to_level(cpt::usize sound_id, cpt::usize level_id);

        /**
         *
         * @param id id of the sound (or alias) to play
         * @return returns if the sound was successfully played
         */
        Result play_sound(cpt::usize id);
        /**
         *
         * @param id id of the sound (or alias) to check
         * @return returns if the sound or at least one of its aliases is currently playing.
         */
        [[nodiscard]] bool is_sound_playing(cpt::usize id) const;

        // music -------------------------------------------------
        // load music collection
        Result load_music_collection(cpt::usize& id, std::vector<std::filesystem::path> const& path);
        // link music collection to sound level
        Result link_music_collection_to_level(cpt::usize sound_id, cpt::usize level_id);
        // play music collection
        Result play_music_collection(cpt::usize id, Fade fade = Fade::Default);
        // pause music collection
        Result pause_music_collection(Fade fade = Fade::Default);
        // resume music collection
        Result resume_music_collection(Fade fade = Fade::Default);
        // stop music collection
        Result stop_music_collection(Fade fade = Fade::Default);
        // switch music collection
        Result switch_music_collection(cpt::usize id, Fade fade = Fade::Default);
        // is specific music collection playing
        [[nodiscard]] bool is_music_collection_playing(cpt::usize id) const;
        // is music collection playing
        [[nodiscard]] bool is_music_playing() const;

        // fade with enum
    };
}
