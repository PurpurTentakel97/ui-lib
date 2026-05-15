//
// Purpur Tentakel
// 15.05.26
//

#pragma once

#include <uil/debug/draw_fps.hpp>
#include <uil/debug/draw_mouse.hpp>

namespace uil::debug {
    struct DebugWindow final {
        DebugFPSDraw fps{};
        DebugMouseDraw mouse{};
    };
} // namespace uil::debug
