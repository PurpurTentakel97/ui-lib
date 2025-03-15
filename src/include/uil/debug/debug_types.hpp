//
// Purpur Tentakel
// 15.03.25
//

#pragma once
#include <cpt/vec2.hpp>
#include <raylib.h>


namespace uil::debug {
    struct MovementDrawDebugData final {
        Vector2 start{};
        Vector2 end{};
        cpt::Vec2_i resolution{};
    };
} // namespace uil::debug
