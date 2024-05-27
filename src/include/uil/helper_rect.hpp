//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <cpt/rect.hpp>
#include <cpt/vec2.hpp>

namespace uil {
    [[nodiscard]] cpt::Rect_f collider_from_relative(cpt::Rect_f relative, cpt::Vec2_i resolution);
    [[nodiscard]] cpt::Rect_f relative_from_collider(cpt::Rect_f collider, cpt::Vec2_i resolution);
} // namespace uil
