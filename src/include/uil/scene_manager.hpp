//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <uil/base_manager.hpp>
#include <uil/scene.hpp>

namespace uil {
    struct Context;

    /**
     * manages all scene in the game.
     * checks, updates, renders and resizes all emplace scenes.
     * stops checking and updating when a scene returns false.
     */
    class SceneManager final : public BaseManager<Scene> {
    public:
        /**
         *
         * @param resolution current resolution
         */
        explicit SceneManager(cpt::Vec2_i resolution);

        /**
         * calls all emplace scene from top to bottom to check.
         * stops checking when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep checking
         */
        [[nodiscard]] bool handle_input(Context const& context) const;

        /**
         * calls all emplace scene from top to bottom to update.
         * stops updating when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep updating
         */
        [[nodiscard]] bool update(Context const& context) const;

        /**
         * calls all emplace scene from bottom to top to render.
         *
         * @param context all changes of the last frame
         */
        void render(Context const& context) const;

        /**
         * calls all emplace scene to resize.
         *
         * @param context all changes of the last frame
         */
        void resize(Context const& context) override;
    };
} // namespace uil
