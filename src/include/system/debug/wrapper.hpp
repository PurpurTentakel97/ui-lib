//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <uil/debug/draw_fps.hpp>
#include <uil/debug/draw_mouse.hpp>
#include <uil/debug/draw_rectangle.hpp>

namespace uil::debug {
    struct Window final {
        FPSDraw fps{};
        MouseDraw mouse{};
    };
} // namespace uil::debug

namespace uil::debug {
    struct Element final {
        RectangleDraw collider{};
    };
} // namespace uil::debug
