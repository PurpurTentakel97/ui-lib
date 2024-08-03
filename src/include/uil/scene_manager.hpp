//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <algorithm>
#include <memory>
#include <uil/scene.hpp>
#include <vector>

namespace uil {
    struct Context;

    /**
     * manages all scene in the game.
     * checks, updates, renders and resizes all emplaced scenes.
     * stops checking and updating when a scene returns false.
     */
    class SceneManager final {
    private:
        std::vector<std::unique_ptr<Scene>> m_scenes{};

        template<std::derived_from<Scene> T, typename... Args>
        T* insert_emelent(cpt::usize const offset, Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto elem      = std::make_unique<T>(std::forward<Args>(args)...);
            auto const ptr = elem.get();
            m_scenes.insert(m_scenes.begin() + static_cast<cpt::i64>(offset), std::move(elem));
            return ptr;
        }

    public:
        /**
         * construct the scene T with parameters Args... and emplaced it at the end of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_back(Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            return insert_emelent<T>(m_scenes.end() - m_scenes.begin(), args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it at the front of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_front(Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            return insert_emelent<T>(0, args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it at a certain index of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param index  provides the index the new scene is empaced to
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         * @throw BadSceneIndex will throw when index is out of range
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_at(cpt::usize const index, Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            if (index > m_scenes.size()) {
                throw BadSceneIndex("index is out of bounce");
            }
            if (index == m_scenes.size()) {
                return emplace_back<T>(args...);
            }

            return insert_emelent<T>(index, args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it after a provided scene of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param before proviedes the scene pointer the new scene gets emplaced before
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         * @throw BadScenePointer throws when provided before scene can not be fount in the scenes vector
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_after(Scene* before, Args... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto const iterator = std::find_if(
                    m_scenes.begin(), m_scenes.end(), [&b = before](auto const& elem) { return elem.get() == b; });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find before element in scenes vector");
            }

            return insert_emelent<T>(iterator - m_scenes.begin() + 1, args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it before a provided scene of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param after proviedes the scene pointer the new scene gets emplaced after
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         * @throw BadScenePointer throws when provided after scene can not be found in the scenes vector
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_before(Scene* after, Args... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto const iterator = std::find_if(
                    m_scenes.begin(), m_scenes.end(), [&a = after](auto const& elem) { return elem.get() == a; });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find after element in scenes vector");
            }

            return insert_emelent<T>(iterator - m_scenes.begin(), args...);
        }

        /**
         * calls all emplaced scene from top to bottom to check.
         * stops checking when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep checking
         */
        [[nodiscard]] bool handle_input(Context const& context) const;
        /**
         * calls all emplaced scene from top to bottom to update.
         * stops updating when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep updting
         */
        [[nodiscard]] bool update(Context const& context) const;
        /**
         * calls all emplaced scene from bottom to top to render.
         *
         * @param context all changes of the last frame
         */
        void render(Context const& context) const;
        /**
         * calls all emplaced scene to resize.
         *
         * @param context all changes of the last frame
         */
        void resize(Context const& context) const;
    };
} // namespace uil
