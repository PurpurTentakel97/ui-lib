//
// Purpur Tentakel
// 15.03.25
//

#pragma once
#include <cpt/vec2.hpp>
#include <raylib.h>


namespace uil::debug {
    struct ColliderWithOffsetDrawDebugData final {
        Vector2 offset{};
        Rectangle collider{};
    };

    struct MovementDrawDebugData final {
        Vector2 start{};
        Vector2 end{};
    };

} // namespace uil::debug
