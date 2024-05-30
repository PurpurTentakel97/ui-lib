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


    [[nodiscard]] Rectangle aligned_position(Rectangle relative, Alignment alignment);
    [[nodiscard]] Rectangle aligned_position_reversed(Rectangle relative, Alignment alignment);
} // namespace uil
