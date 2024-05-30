//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <raylib.h>
#include <cpt/vec2.hpp>

namespace uil {
    [[nodiscard]] Rectangle collider_from_relative(Rectangle relative, cpt::Vec2_i resolution);
    [[nodiscard]] Rectangle relative_from_collider(Rectangle collider, cpt::Vec2_i resolution);
} // namespace uil
