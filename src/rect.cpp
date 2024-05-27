//
// Purpur Tentakel
// 24.05.24
//

#include "uil/rect.hpp"

namespace uil {
    Rect uil::collider_from_relative(Rect const relative, cpt::Vec2i const resolution) {
        // clang-format off
        return {
            relative.x * resolution.x,
            relative.y * resolution.y,
            relative.width * resolution.x,
            relative.height * resolution.y
        };
        // clang-format on
    }
    Rect uil::relative_from_collider(Rect const collider, cpt::Vec2i const resolution) {
        return {
            // clang-format off
            collider.x / resolution.x,
            collider.y / resolution.y,
            collider.width / resolution.x,
            collider.height / resolution.y
            // clang-format on
        };
    }
} // namespace uil
