//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <string>
#include <vector>

namespace uil {
    enum class Resolution {
        // 16:9
        UHD2,
        _5K,
        UHD1,
        WQHD,
        FULL_HD,
        HD,

        // 21:9
        _5K_ULTRA_WIDE,
        UWQHD,
        UWHD,

        // 4:3
        QXGA,
        UXGA,
        SXGA_Plus,
        XGA_Plus,
        XGA,
        SVGA,
        PAL,
        VGA,

        SCREEN,
        CUSTOM, // CUSTOM needs to stay last entry
    };

    [[nodiscard]] cpt::Vec2_i vec_from_resolution(Resolution resolution, cpt::Vec2_i current_resolution);
    [[nodiscard]] std::string str_from_resolution(Resolution resolution, cpt::Vec2_i current_resolution);
    [[nodiscard]] std::vector<std::string> all_string_from_resolution(cpt::Vec2_i current_resolution);

} // namespace uil
