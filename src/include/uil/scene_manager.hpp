//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <uil/base_manager.hpp>
#include <uil/scene.hpp>

namespace uil {
    struct UpdateContext;

    /**
     * manages all scene in the game.
     * checks, updates, renders and resizes all emplace scenes.
     * stops checking and updating when a scene returns false.
     */
    class SceneManager final : public BaseManager<Scene> {
    public:
        using BaseManager::BaseManager;

        /**
         * calls all emplace scene from top to bottom to check.
         * stops checking when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep checking
         */
        [[nodiscard]] bool handle_input(UpdateContext const& context) const;

        /**
         * calls all emplace scene from top to bottom to update.
         * stops updating when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep updating
         */
        [[nodiscard]] bool update(UpdateContext const& context) const;

        /**
         * calls all emplace scene from bottom to top to render.
         *
         * @param context all changes of the last frame
         */
        void render(UpdateContext const& context) const;

        /**
         * calls all emplace scene to resize.
         */
        void resize() override;
    };
} // namespace uil
