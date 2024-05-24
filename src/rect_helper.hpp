//
// Purpur Tentakel
// 24.05.24
//

#pragma once

#include <raylib.h>
#include <uil/rect.hpp>

namespace uil {
    [[nodiscard]] inline Rectangle rect_to_ray(Rect rect) {
        return { rect.x, rect.y, rect.width, rect.height };
    }
    [[nodisacrd]] inline Rect ray_to_rect(Rectangle rectangle) {
        return { rectangle.x, rectangle.y, rectangle.width, rectangle.height };
    }
} // namespace uil
