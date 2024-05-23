//
// Purpur Tentakel
// 23.05.24
//

#pragma once

#include <cpt/Vec2.hpp>

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


    [[nodiscard]] cpt::Vec2f aligned_position(cpt::Vec2f pos, cpt::Vec2f size, Alignment alignment);
    [[nodiscard]] cpt::Vec2f aligned_position_reversed(cpt::Vec2f pos, cpt::Vec2f size, Alignment alignment);
} // namespace uil
