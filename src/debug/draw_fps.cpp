//
// Purpur Tentakel
// 15.05.26
//

#include <raylib.h>
#include <string>
#include <uil/debug/draw_fps.hpp>

namespace uil::debug {
    void DebugFPSDraw::exec(void const*) const {
#ifndef NDEBUG
        if (m_active) {
            DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 50, WHITE);
        }
#endif
    }
} // namespace uil::debug
