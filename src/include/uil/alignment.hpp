//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <raylib.h>

namespace uil {
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

    enum class HorizontalAlignment {
        Left,
        Mid,
        Right,
    };

    enum class VerticalAlignment {
        Top,
        Mid,
        Bottom,
    };


    [[nodiscard]] Rectangle aligned_position(Rectangle relative, Alignment alignment);
    [[nodiscard]] Rectangle aligned_position_reversed(Rectangle relative, Alignment alignment);

    [[nodiscard]] Rectangle horizontal_aligned_position(Rectangle relative, HorizontalAlignment alignment);
    [[nodiscard]] Rectangle horizontal_aligned_position_reversed(Rectangle relative, HorizontalAlignment alignment);

    [[nodiscard]] Rectangle vertical_aligned_position(Rectangle relative, VerticalAlignment alignment);
    [[nodiscard]] Rectangle vertical_aligned_position_reversed(Rectangle relative, VerticalAlignment alignment);

    [[nodiscard]] Vector2 aligned_position(Vector2 const& point, Vector2 const& size, Alignment const& alignment);
    [[nodiscard]] Vector2 aligned_position_reversed(Vector2 const& point,
                                                    Vector2 const& size,
                                                    Alignment const& alignment);

    [[nodiscard]] Vector2 horizontal_aligned_position(Vector2 const& point,
                                                               Vector2 const& size,
                                                               HorizontalAlignment const& alignment);
    [[nodiscard]] Vector2 horizontal_aligned_position_reversed(Vector2 const& point,
                                                               Vector2 const& size,
                                                               HorizontalAlignment const& alignment);

    [[nodiscard]] Vector2 vertical_aligned_position(Vector2 const& point,
                                                             Vector2 const& size,
                                                             VerticalAlignment const& alignment);
    [[nodiscard]] Vector2 vertical_aligned_position_reversed(Vector2 const& point,
                                                             Vector2 const& size,
                                                             VerticalAlignment const& alignment);

    [[nodiscard]] HorizontalAlignment to_horizontal_alignment(Alignment alignment);
    [[nodiscard]] VerticalAlignment to_vertical_alignment(Alignment alignment);
    [[nodiscard]] Alignment to_alignment(VerticalAlignment vertical_alignment,
                                         HorizontalAlignment horizontal_alignment);
} // namespace uil
