//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <raylib.h>
#include <cpt/vec2.hpp>

namespace uil {
    /**
     * calculates absolute values from relative values and resolution
     *
     * @param relative relative position and size
     * @param resolution current resolution
     * @return absolute position and size
     */
    [[nodiscard]] Rectangle collider_from_relative(Rectangle relative, cpt::Vec2_i resolution);

    /**
     * calculates reative values from absolute values and resolution
     *
     * @param collider absolute position and size
     * @param resolution current resolution
     * @return relative position and size
     */
    [[nodiscard]] Rectangle relative_from_collider(Rectangle collider, cpt::Vec2_i resolution);

    /**
     * extraxts the positon of a rectangle.
     * should work with relative and absolute values.
     *
     * @param rect position and size
     * @return position
     */
    [[nodiscard]] Vector2 point_from_rect(Rectangle const& rect);

    /**
     * extraxts the size of a rectangle.
     * should work with relative and absolute values.
     *
     * @param rect position and size
     * @return size
     */
    [[nodiscard]] Vector2 size_from_rect(Rectangle const& rect);

    /**
     * combines position and size to a rectangle.
     * should work with relative and absolute values.
     *
     * @param point position
     * @param size size
     * @return position and size
     */
    [[nodiscard]] Rectangle rect_from_point_and_size(Vector2 const& point, Vector2 const& size);
} // namespace uil
