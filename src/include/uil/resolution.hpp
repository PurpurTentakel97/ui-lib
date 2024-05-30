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
        QUAD_UHD,
        FULL_UHD,
        UHD_Plus,
        UHD,
        WQHD,
        FULL_HD,
        HD,
        HD_540,
        HD_360,

        // 18:9
        FULL_HD_Plus,
        Quad_HD_Plus,

        // 21:9
        UWQHD,
        WUHD,
        UWFHD,

        // 4:3
        HUXGA,
        HXGA,
        QUXGA,
        QSXGA_Plus,
        QXGA,
        UXGA,
        SXGA_Plus,
        SXVGA,
        XGA,
        SVGA,
        VGA,
        QSVGA,
        QVGA,

        SCREEN,
        CUSTOM, // CUSTOM needs to stay last entry
    };

    [[nodiscard]] cpt::Vec2_i vec_from_resolution(Resolution resolution);
    [[nodiscard]] std::string str_from_resolution(Resolution resolution);
    [[nodiscard]] std::vector<std::string> all_string_from_resolution();

} // namespace uil
