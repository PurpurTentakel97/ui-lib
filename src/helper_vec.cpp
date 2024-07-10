//
// Purpur Tentakel
// 06.07.24
//

#include <cmath>
#include <uil/helper_vec.hpp>

namespace uil {
    float magnitude(Vector2 const& vec) {
        return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
    }

    Vector2 normalize(Vector2 const& vec) {
        auto const mag = magnitude(vec);
        return { vec.x / mag, vec.y / mag };
    }
} // namespace uil
