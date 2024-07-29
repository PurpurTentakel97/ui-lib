//
// Purpur Tentakel
// 06.07.24
//

#pragma once
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

    public:
        /**
         * construct the scene T with parameters Args... and emplaced it into the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T acene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param args all Parameters the scene needs to be constructed
         * @return reference of the constructed scene
         */
        template<std::derived_from<Scene> T, typename... Args>
        T& emplace_scene(Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto elem = std::make_unique<T>(std::forward<Args>(args)...);
            auto const temp = elem.get();
            m_scenes.push_back(std::move(elem));
            return *temp;
        }

        /**
         * calls all emplaced scene from top to bottom to check.
         * stops checking when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep checking
         */
        [[nodiscard]] bool check(Context const& context) const;
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
         * stops rendering when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep updting
         */
        [[nodiscard]] bool render(Context const& context) const;
        /**
         * calls all emplaced scene to resize.
         *
         * @param context all changes of the last frame
         */
        void resize(Context const& context) const;
    };
} // namespace uil
