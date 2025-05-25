//
// Purpur Tentakel
// 30.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <raylib.h>

namespace uil {
    class SceneManager;

    /**
     * provides all values for check, update, render and resize
     */
    struct UpdateContext final {
        Vector2 mouse_position;
        Font const* font;
        cpt::Vec2_i resolution;
        float delta_time;
        SceneManager& scene_manager;

        /**
         * all values should be from the beginning of the frame
         *
         * @param _mouse_position current mouse position
         * @param _font current font pointer
         * @param _resolution current resolution
         * @param _delta_time time of the last frame
         * @param _scene_manager reference of the scene_manager
         */
        UpdateContext(Vector2 _mouse_position,
                      Font const* _font,
                      cpt::Vec2_i _resolution,
                      float _delta_time,
                      SceneManager& _scene_manager);
        UpdateContext() = delete;
    };
}
