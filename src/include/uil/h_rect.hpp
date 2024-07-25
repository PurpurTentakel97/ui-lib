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

    [[nodiscard]] Vector2 point_from_rect(Rectangle const& rect);

    [[nodiscard]] Vector2 size_from_rect(Rectangle const& rect);

    [[nodiscard]] Rectangle rect_from_point_and_size(Vector2 const& point, Vector2 const& size);
} // namespace uil
