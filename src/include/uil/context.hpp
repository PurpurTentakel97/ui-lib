//
// Purpur Tentakel
// 30.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <raylib.h>

namespace uil {
    struct Context final {
        Vector2 mouse_position;
        Font const* font;
        cpt::Vec2_i resolution;
    };
}
