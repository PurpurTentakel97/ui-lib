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

    Vector2 to_absolute(Vector2 const& relative, cpt::Vec2_i const& resolution) {
        // clang-format off
        return {
            relative.x * static_cast<float>(resolution.x),
            relative.y * static_cast<float>(resolution.y)
        };
        // clang-format on
    }

    Vector2 to_relative(Vector2 const& absolute, cpt::Vec2_i const& resolution) {
        // clang-format off
        return {
            absolute.x / static_cast<float>(resolution.x),
            absolute.y / static_cast<float>(resolution.y)
        };
        // clang-format on
    }
} // namespace uil
