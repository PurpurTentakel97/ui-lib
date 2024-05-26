//
// Purpur Tentakel
// 24.05.24
//

#include <uil/helper_rect.hpp>

namespace uil {
    cpt::Rect_f collider_from_relative(cpt::Rect_f const relative, cpt::Vec2_i const resolution) {
        return { relative.x * static_cast<float>(resolution.x),
                 relative.y * static_cast<float>(resolution.y),
                 relative.width * static_cast<float>(resolution.x),
                 relative.height * static_cast<float>(resolution.y) };
    }
    cpt::Rect_f relative_from_collider(cpt::Rect_f const collider, cpt::Vec2_i const resolution) {
        return { collider.x / static_cast<float>(resolution.x),
                 collider.y / static_cast<float>(resolution.y),
                 collider.width / static_cast<float>(resolution.x),
                 collider.height / static_cast<float>(resolution.y) };
    }
} // namespace uil
