//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <string>
#include <vector>

namespace uil {
    /**
     * contains all predefined resolutions.
     */
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

        RESIZED,
        CUSTOM,
        SCREEN, // the screen needs to stay last
    };

    /**
     * lookup of height and with from the provided resolution enum.
     *
     * @param resolution resolution enum
     * @return height and width in pixels
     * @throw uil::BadResolution unexpected resolution enum. mostly happens when the enum has a non predefined value.
     */
    [[nodiscard]] cpt::Vec2_i vec_from_resolution(Resolution resolution);
    /**
     * lookup of a string representation from the provided resolution enum.
     *
     * @param resolution resolution enum
     * @return string representation
     * @throw uil::BadResolution unexpected resolution enum. mostly happens when the enum has a non predefined value.
     */
    [[nodiscard]] std::string str_from_resolution(Resolution resolution);
    /**
     * lookup for all string representations from all resolution enums.
     *
     * @return vector of all string representations
     * @throw uil::BadResolution because ist calls str_from_resolution().
     */
    [[nodiscard]] std::vector<std::string> all_string_from_resolution();

} // namespace uil
