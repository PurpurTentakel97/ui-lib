//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <uil/rect.hpp>

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


    [[nodiscard]] Rect aligned_position(Rect relative, Alignment alignment);
    [[nodiscard]] Rect aligned_position_reversed(Rect relative, Alignment alignment);
} // namespace uil
