//
// Purpur Tentakel
// 26.05.25
//

#include <raylib.h>
#include <string>
#include <uil/debug/classes.hpp>

namespace uil::debug {

    void FPSDraw::exec(void const*) const {
#ifndef NDEBUG
        if (m_active) {
            DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 50, WHITE);
        }
#endif
    }
} // namespace uil::debug
