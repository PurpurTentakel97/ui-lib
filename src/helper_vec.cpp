//
// Purpur Tentakel
// 06.07.24
//

#include <cmath>
#include <uil/exception.hpp>
#include <uil/helper_vec.hpp>

namespace uil {
    float magnitude(Vector2 const& vec) {
        return std::sqrt((vec.x * vec.x) + (vec.y * vec.y));
    }

    Vector2 normalize(Vector2 const& vec) {
        auto const mag = magnitude(vec);
        if (mag == 0.0f) {
            throw DivideByZero("Devide by 0.0f while normalize a Vector2");
        }
        return { vec.x / mag, vec.y / mag };
    }
} // namespace uil
