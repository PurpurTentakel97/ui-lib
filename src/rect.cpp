//
// Purpur Tentakel
// 24.05.24
//

#include "uil/rect.hpp"

namespace uil {
    Rect uil::collider_from_relative(cpt::Vec2f pos, cpt::Vec2f size, cpt::Vec2i resolution) {
        // clang-format off
        return {
            pos.x * resolution.x,
            pos.y * resolution.y,
            size.x * resolution.x,
            size.y * resolution.y
        };
        // clang-format on
    }
    std::pair<cpt::Vec2f, cpt::Vec2f> uil::relative_from_collider(Rect collider, cpt::Vec2i resolution) {
        return {
  // clang-format off
            {
                collider.x / resolution.x,
                collider.y / resolution.y
            },
            {
                collider.width / resolution.x,
                collider.height / resolution.y
            }
  // clang-format on
        };
    }
} // namespace uil
