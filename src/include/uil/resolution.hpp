//
// Purpur Tentakel
// 19.05.24
//

#pragma once

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
        XGA_plus,
        XGA,
        SVGA,
        PAL,
        VGA,

        SCREEN,
        CUSTOM,
    };
} // namespace uil
