//
// Purpur Tentakel
// 17.04.25
//

#pragma once

#include <unordered_map>
#include <cpt/types.hpp>
#include <vector>
#include <filesystem>
#include <optional>
#include <tl/expected.hpp>
#include <cpt/log.hpp>

namespace uil {
    template<typename T>
    concept IsSoundFile = std::is_same_v<T, Sound> or std::is_same_v<T, Music>;

    class SoundManager final {
    public:
        // #region Result
        /**
         * Describes the Result of a Sound Operation
         */
        enum class Result {
            InvalidPath,
            EmptyContainer,

            UnknownLevelID,
            UnknownSoundID,
            UnknownMusicCollectionID,

            StillMusicPlaying,
            NoMusicPlaying,
            NoCurrentMusic,

            Success,
        };

        /**
         *
         * @param result to check
         * @return if the provided result indicates a success
         */
        [[nodiscard]] static bool is_success(Result result);
        // #endregion

    private:
        // #region Internal
        struct LevelEntry final {
            float value{};
            bool muted{ false };
        };

        struct SoundEntry final {
            std::vector<Sound> sound{};
            cpt::usize level_id{ 0 };
        };

        struct MusicEntry final {
            std::vector<Music> music{};
            cpt::usize level_id{ 0 };
        };

        std::unordered_map<cpt::usize, LevelEntry> m_levels{ { 0, { 1.0f } } };

        std::unordered_map<cpt::usize, SoundEntry> m_sounds{};

        std::unordered_map<cpt::usize, MusicEntry> m_music_collections{};
        std::optional<MusicEntry*> m_current_music_collection{};
        std::optional<MusicEntry*> m_next_music_collection{};
        std::optional<Music*> m_current_music{};
        cpt::usize m_next_music_index{ 0 };
        bool m_is_music_paused{ false };

        [[nodiscard]] LevelEntry& main_level();
        [[nodiscard]] static bool is_main_level(cpt::usize level_id);


        void update_current_music_level(cpt::usize level_id);

        void update_current_music_collection();
        // #endregion

        // #region Ray
        template<IsSoundFile T>
        Result set_level_ray(T const& file, cpt::usize const level_id) {
            if (not m_levels.contains(level_id)) {
                cpt::log::r_error("[[Sound Manager]] | Level with ID '{}' not found", level_id);
                return Result::UnknownLevelID;
            }

            auto const level = [this, &level_id]() {
                if (main_level().muted) { return 0.0f; }
                if (m_levels.at(level_id).muted) { return 0.0f; }

                if (is_main_level(level_id)) {
                    return main_level().value;
                }
                return m_levels.at(level_id).value * main_level().value;
            }();

            if constexpr (std::is_same_v<T, Sound>) {
                SetSoundVolume(file, level);
                return Result::Success;
            }
            if constexpr (std::is_same_v<T, Music>) {
                SetMusicVolume(file, level);
                return Result::Success;
            }
        }

        // #endregion

    public:
        // #region Constructor
        SoundManager();
        SoundManager(SoundManager const&)            = delete;
        SoundManager(SoundManager&&)                 = delete;
        SoundManager& operator=(SoundManager const&) = delete;
        SoundManager& operator=(SoundManager&&)      = delete;
        ~SoundManager();
        // #endregion

        // #region Global
        /**
         * updates the music streams and fades.
         */
        void update();
        // #endregion

        // #region Level
        /**
         * call this to add a new level id by just providing an unknown id here.
         * call this with id 0 to set the global level
         *
         * @param id of the level to set (0 is the global level)
         * @param level amount that the level gets set to. 0.0f - 1.0f
         */
        void set_level(cpt::usize id, float level);

        /**
         * call it with id 0 to get the main level.
         * it returns 0 when the id is not existing.
         * note that the main level also affects every other level.
         *
         * @param id of the level to get (0 == main level)
         * @return the current value of the provided level id
         */
        [[nodiscard]] float get_level(cpt::usize id) const;

        /**
         *
         * @param id of the sound level to toggle
         * @return if the toggle was successful
         */
        Result toggle_mute_sound_level(cpt::usize id);

        /**
         *
         * @param id of the sound level to set
         * @param is_mute the value the sound level gets sets to
         * @return if the set was successful
         */
        Result set_mute_sound_level(cpt::usize id, bool is_mute);

        /**
         *
         * @param id of the sound level to check
         * @return if the provided sound level is muted. returns false if the provided id is not existing
         */
        [[nodiscard]] bool is_sound_level_muted(cpt::usize id) const;
        // #endregion

        // #region Sound
        /**
         *
         * @param path provides the path of the loaded sound. Can be a relative or an absolute path. A relative Path will be called with the working directory
         * @param alias_pre_load_count loads an initial amound of aliases. Use this if sounds should overlap
         * @return returns either the id or an error
         */
        tl::expected<cpt::usize, Result> load_sound(std::filesystem::path const& path,
                                                    cpt::usize alias_pre_load_count = 0);
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
        // #endregion

        // #region Music
        /**
         *
         * @param path a vector of path's that gets loaded into one collection
         * @return returns either the id or an error
         */
        tl::expected<cpt::usize, Result> load_music_collection(std::vector<std::filesystem::path> const& path);
        /**
         *
         * @param music_collection_id provides the collection ID the gets linked
         * @param level_id provides the level ID where the collection gets linked to
         * @return result of the Sound operation
         */
        Result link_music_collection_to_level(cpt::usize music_collection_id, cpt::usize level_id);
        /**
         *
         * @param id of the music collection that gets started
         * @return result of the Sound operation
         */
        Result start_music_collection(cpt::usize id);
        /**
         * pauses the current music collection. it can be resumed after that.
         * @return result of the Sound operation
         */
        Result pause_music_collection();
        /**
         * resumes the current music collection if there is one.
         * @return result of the Sound operation
         */
        Result resume_music_collection();
        /**
         * stops the current music collection. it can not be resumed.
         * @return result of the Sound operation
         */
        Result stop_music_collection();
        /**
         * stops the current music collection and starts a new one.
         * @param id of the next music collection
         * @return result of the Sound operation
         */
        Result switch_music_collection(cpt::usize id);
        /**
         *
         * @param id if of the music collection that gets checked
         * @return returns if any song of the given music collection is playing. returns false if the provided id is not existing
         */
        [[nodiscard]] bool is_music_collection_playing(cpt::usize id) const;
        /**
         *
         * @return if the current music is playing. Also returns false if there is no current music set yet.
         */
        [[nodiscard]] bool is_music_playing() const;
        // #endregion
    };
}
