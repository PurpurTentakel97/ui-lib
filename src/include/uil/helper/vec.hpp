//
// Purpur Tentakel
// 10.07.24
//

#pragma once
#include <cpt/vec2.hpp>
#include <raylib.h>
#include <uil/exception.hpp>

namespace uil {
    /**
     * calculates the legth of a vector2
     *
     * @param vec provided vector
     * @return length of the vector
     */
    [[nodiscard]] float magnitude(Vector2 const& vec);

    /**
     * calculates a vector with length 1 that point into the same direction as the provided one.
     *
     * @param vec provided vector
     * @return vector with length 1
     */
    [[nodiscard]] Vector2 normalize(Vector2 const& vec);

    /**
     * calculates absolute values out of relative values and resolution
     *
     * @param relative relative value
     * @param resolution current resolution
     * @return absolute value
     */
    [[nodiscard]] Vector2 to_absolute(Vector2 const& relative, cpt::Vec2_i const& resolution);

    /**
     * calculates relative values out of absolute values and resolution
     *
     * @param absolute absolute values
     * @param resolution current resolution
     * @return relative values
     */
    [[nodiscard]] Vector2 to_relative(Vector2 const& absolute, cpt::Vec2_i const& resolution);
} // namespace uil

/**
 * provides a operator += for raylib type Vector2 that overrides lhs.
 *
 * @param lhs left vector
 * @param rhs right vector
 * @return overrides lhs vector
 */
inline Vector2& operator+=(Vector2& lhs, Vector2 const& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

/**
 * provides a operator+ for raylib type Vecpor2 that returns a new vector.
 *
 * @param lhs left vector
 * @param rhs right vector
 * @return new result vector
 */
[[nodiscard]] inline Vector2 operator+(Vector2 lhs, Vector2 const& rhs) {
    lhs += rhs;
    return lhs;
}

/**
 * provides a operator -= for raylib type Vector2 that overrides lhs.
 *
 * @param lhs left vector
 * @param rhs right vector
 * @return overrides lhs vector
 */
inline Vector2& operator-=(Vector2& lhs, Vector2 const& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}
/**
 * provides a operator- for raylib type Vecpor2 that returns a new vector.
 *
 * @param lhs left vector
 * @param rhs right vector
 * @return new result vector
 */
[[nodiscard]] inline Vector2 operator-(Vector2 lhs, Vector2 const& rhs) {
    lhs -= rhs;
    return lhs;
}

/**
 * provides a operator *= for raylib type Vector2 that overrides lhs.
 *
 * @param lhs left vector
 * @param rhs float
 * @return overrides lhs vector
 */
inline Vector2 operator*=(Vector2& lhs, float const rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}
/**
 * provides a operator* for raylib type Vecpor2 that returns a new vector.
 *
 * @param lhs left vector
 * @param rhs float
 * @return new result vector
 */
[[nodiscard]] inline Vector2 operator*(Vector2 lhs, float const rhs) {
    lhs *= rhs;
    return lhs;
}

/**
 * provides a operator /= for raylib type Vector2 that overrides lhs.
 *
 * @param lhs left vector
 * @param rhs float
 * @return overrides lhs vector
 * @throw uil::DivideByZero when rhs is 0.0f
 */
inline Vector2 operator/=(Vector2& lhs, float const rhs) {
    if (rhs == 0.0f) {
        throw uil::DivideByZero("Devide by zero while deviding a vector by a float");
    }
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}
/**
 * provides a operator* for raylib type Vecpor2 that returns a new vector.
 *
 * @param lhs left vector
 * @param rhs float
 * @return new result vector
 * @throw uil::DivideByZero when rhs is 0.0f
 */
[[nodiscard]] inline Vector2 operator/(Vector2 lhs, float const rhs) {
    lhs /= rhs;
    return lhs;
}
