//
// Purpur Tentakel
// 15.05.26
//

#pragma once

#include <uil/debug/draw_fps.hpp>
#include <uil/debug/draw_mouse.hpp>

namespace uil::debug {
    struct Window final {
        FPSDraw fps{};
        MouseDraw mouse{};
    };
} // namespace uil::debug
