//
// Purpur Tentakel
// 15.05.26
//

#include <raylib.h>
#include <uil/debug/draw_rectangle.hpp>

namespace uil::debug {
    void RectangleDraw::exec([[maybe_unused]] Rectangle const* rect) const {
#ifndef NDEBUG
        if (m_active) {
            DrawRectangleLinesEx(*rect, 1.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug
