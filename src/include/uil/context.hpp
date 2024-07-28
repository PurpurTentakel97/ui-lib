//
// Purpur Tentakel
// 30.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <raylib.h>

namespace uil {
    /**
     * provides all values for check, update, render and resize
     */
    struct Context final {
        Vector2 mouse_position;
        Font const* font;
        cpt::Vec2_i resolution;

        /**
         * all values should be from the beginning of the frame
         *
         * @param _mouse_position current mouse position
         * @param _font current font pointer
         * @param _resolution current resolution
         */
        Context(Vector2 _mouse_position, Font const* _font, cpt::Vec2_i _resolution);
        Context() = delete;
    };
}
