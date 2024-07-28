//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <raylib.h>

namespace uil {
    /**
     * provides a sinple alignement that can display 9 position
     */
    enum class Alignment {
        TopLeft,
        TopMid,
        TopRight,
        MidLeft,
        MidMid,
        MidRight,
        BottomLeft,
        BottomMid,
        BottomRight,
    };

    /**
     * provides a simple version of uil::Alignment for horizontal position
     */
    enum class HorizontalAlignment {
        Left,
        Mid,
        Right,
    };

    /**
     * provides a simple version of uil::Alignment for vertical position
     */
    enum class VerticalAlignment {
        Top,
        Mid,
        Bottom,
    };


    /**
     * moves the rectangle accoding to the provided alignement.
     *
     * @param relative unaligned position and size
     * @param alignment alignment
     * @return aligned position and size
     */
    [[nodiscard]] Rectangle aligned_position(Rectangle relative, Alignment alignment);
    /**
     * moves the ractangle back according to the provided alignement.
     *
     * @param relative aligned position and size
     * @param alignment alignment
     * @return unaligned position and size
     */
    [[nodiscard]] Rectangle aligned_position_reversed(Rectangle relative, Alignment alignment);

    /**
     * moves the rectangle accoding to the provided alignment horizontal.
     *
     * @param relative unaligned position and size
     * @param alignment horizontal alignment
     * @return aligned position and size
     */
    [[nodiscard]] Rectangle horizontal_aligned_position(Rectangle relative, HorizontalAlignment alignment);
    /**
     * moves the ractangle back according to the provided alignement horizontal.
     *
     * @param relative aligned position and size
     * @param alignment horizontal alignment
     * @return unaligned position and size
     */
    [[nodiscard]] Rectangle horizontal_aligned_position_reversed(Rectangle relative, HorizontalAlignment alignment);

    /**
     * moves the rectangle accoding to the provided alignment vertical.
     *
     * @param relative unaligned position and size
     * @param alignment vertical alignment
     * @return aligned position and size
     */
    [[nodiscard]] Rectangle vertical_aligned_position(Rectangle relative, VerticalAlignment alignment);
    /**
     * moves the ractangle back according to the provided alignement vertical.
     *
     * @param relative aligned position and size
     * @param alignment horizontal alignment
     * @return unaligned position and size
     */
    [[nodiscard]] Rectangle vertical_aligned_position_reversed(Rectangle relative, VerticalAlignment alignment);

    /**
     * moves the position according to the provided alignment.
     *
     * @param point unaligned position
     * @param size size
     * @param alignment alignment
     * @return aligned position
     */
    [[nodiscard]] Vector2 aligned_position(Vector2 const& point, Vector2 const& size, Alignment const& alignment);
    /**
     * moved the position back according to the provided alignment.
     *
     * @param point aligned position
     * @param size size
     * @param alignment alignment
     * @return unaligned position
     */
    [[nodiscard]] Vector2 aligned_position_reversed(Vector2 const& point,
                                                    Vector2 const& size,
                                                    Alignment const& alignment);

    /**
     * moves the position according to the provided horizontal alignment.
     *
     * @param point unaligned position
     * @param size size
     * @param alignment horizontal alignment
     * @return aligned position
     */
    [[nodiscard]] Vector2 horizontal_aligned_position(Vector2 const& point,
                                                               Vector2 const& size,
                                                               HorizontalAlignment const& alignment);
    /**
     * moved the position back according to the provided horizontal alignment.
     *
     * @param point aligned position
     * @param size size
     * @param alignment horizontal alignment
     * @return unaligned position
     */
    [[nodiscard]] Vector2 horizontal_aligned_position_reversed(Vector2 const& point,
                                                               Vector2 const& size,
                                                               HorizontalAlignment const& alignment);

    /**
     * moves the position according to the provided vertical alignment.
     *
     * @param point unaligned position
     * @param size size
     * @param alignment vertical alignment
     * @return aligned position
     */
    [[nodiscard]] Vector2 vertical_aligned_position(Vector2 const& point,
                                                             Vector2 const& size,
                                                             VerticalAlignment const& alignment);
    /**
     * moved the position back according to the provided vertical alignment.
     *
     * @param point aligned position
     * @param size size
     * @param alignment vertical alignment
     * @return unaligned position
     */
    [[nodiscard]] Vector2 vertical_aligned_position_reversed(Vector2 const& point,
                                                             Vector2 const& size,
                                                             VerticalAlignment const& alignment);

    /**
     * provides the horizontal alignment out of a alignment.
     *
     * @param alignment alignment
     * @return horizontal alignment
     */
    [[nodiscard]] HorizontalAlignment to_horizontal_alignment(Alignment alignment);
    /**
     * provides the vertical alignment out of a alignment.
     *
     * @param alignment alignment
     * @return vertical alignment
     */
    [[nodiscard]] VerticalAlignment to_vertical_alignment(Alignment alignment);
    /**
     * provides a alignment out auf a vertical and horizontal alignment.
     *
     * @param vertical_alignment vertical alignment
     * @param horizontal_alignment horizontal alignment
     * @return alignment
     */
    [[nodiscard]] Alignment to_alignment(VerticalAlignment vertical_alignment,
                                         HorizontalAlignment horizontal_alignment);
} // namespace uil
