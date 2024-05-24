//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <cpt/Vec2.hpp>
#include <utility>

namespace uil {
    struct Rect final {
        float x;
        float y;
        float width;
        float height;
    };

    [[nodiscard]] Rect collider_from_relative(Rect relative, cpt::Vec2i resolution);
    [[nodiscard]] Rect relative_from_collider(Rect collider, cpt::Vec2i resolution);
} // namespace uil
