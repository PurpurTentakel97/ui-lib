//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <uil/helper_rect.hpp>

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


    [[nodiscard]] cpt::Rect_f aligned_position(cpt::Rect_f relative, Alignment alignment);
    [[nodiscard]] cpt::Rect_f aligned_position_reversed(cpt::Rect_f relative, Alignment alignment);
} // namespace uil
