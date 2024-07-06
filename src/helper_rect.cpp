//
// Purpur Tentakel
// 24.05.24
//

#include <uil/helper_rect.hpp>
#include <uil/exception.hpp>

namespace uil {
    Rectangle collider_from_relative(Rectangle const relative, cpt::Vec2_i const resolution) {
        return { relative.x * static_cast<float>(resolution.x),
                 relative.y * static_cast<float>(resolution.y),
                 relative.width * static_cast<float>(resolution.x),
                 relative.height * static_cast<float>(resolution.y) };
    }

    Rectangle relative_from_collider(Rectangle const collider, cpt::Vec2_i const resolution) {
        if (resolution.x == 0 or resolution.y == 0){
            throw DivideByZero("resolution width or height was zero");
        }
        return { collider.x / static_cast<float>(resolution.x),
                 collider.y / static_cast<float>(resolution.y),
                 collider.width / static_cast<float>(resolution.x),
                 collider.height / static_cast<float>(resolution.y) };
    }
} // namespace uil
