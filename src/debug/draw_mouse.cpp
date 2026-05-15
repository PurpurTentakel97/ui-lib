//
// Purpur Tentakel
// 15.05.26
//

#include <raylib.h>
#include <uil/debug/draw_mouse.hpp>

namespace uil::debug {
    void DebugMouseDraw::exec(void const*) const {
#ifndef NDEBUG
        if (m_active) {
            DrawCircleLinesV(GetMousePosition(), 10.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug
