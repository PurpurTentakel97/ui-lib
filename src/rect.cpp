//
// Purpur Tentakel
// 24.05.24
//

#include "uil/rect.hpp"

namespace uil {
    Rect collider_from_relative(Rect const relative, cpt::Vec2i const resolution) {
        return { relative.x * static_cast<float>(resolution.x),
                 relative.y * static_cast<float>(resolution.y),
                 relative.width * static_cast<float>(resolution.x),
                 relative.height * static_cast<float>(resolution.y) };
    }
    Rect relative_from_collider(Rect const collider, cpt::Vec2i const resolution) {
        return { collider.x / static_cast<float>(resolution.x),
                 collider.y / static_cast<float>(resolution.y),
                 collider.width / static_cast<float>(resolution.x),
                 collider.height / static_cast<float>(resolution.y) };
    }
} // namespace uil
