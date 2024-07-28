//
// Purpur Tentakel
// 10.07.24
//

#pragma once
#include <cpt/vec2.hpp>
#include <raylib.h>
#include <uil/exception.hpp>

namespace uil {
    [[nodiscard]] float magnitude(Vector2 const& vec);

    [[nodiscard]] Vector2 normalize(Vector2 const& vec);

    [[nodiscard]] Vector2 to_absolute(Vector2 const& relative, cpt::Vec2_i const& resolution);

    [[nodiscard]] Vector2 to_relative(Vector2 const& absolute, cpt::Vec2_i const& resolution);
} // namespace uil

inline Vector2& operator+=(Vector2& lhs, Vector2 const& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
[[nodiscard]] inline Vector2 operator+(Vector2 lhs, Vector2 const& rhs) {
    lhs += rhs;
    return lhs;
}

inline Vector2& operator-=(Vector2& lhs, Vector2 const& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
[[nodiscard]] inline Vector2 operator-(Vector2 lhs, Vector2 const& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Vector2 operator*=(Vector2& lhs, float const rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}
[[nodiscard]] inline Vector2 operator*(Vector2 lhs, float const rhs) {
    lhs *= rhs;
    return lhs;
}

inline Vector2 operator/=(Vector2& lhs, float const rhs) {
    if (rhs == 0.0f) {
        throw uil::DivideByZero("Devide by zero while deviding a vector by a float");
    }
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}
[[nodiscard]] inline Vector2 operator/(Vector2 lhs, float const rhs) {
    lhs /= rhs;
    return lhs;
}