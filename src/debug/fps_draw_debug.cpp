//
// Purpur Tentakel
// 15.03.25
//

#include <string>
#include <uil/debug/fps_draw_debug.hpp>
#include <uil/window.hpp>

namespace uil::debug {
    void FpsDebug::exec(Window const&) const {
#ifndef NDEBUG
        if (m_value) {
            DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 50, WHITE);
        }
#endif
    }
} // namespace uil::debug
