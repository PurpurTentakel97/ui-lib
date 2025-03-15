//
// Purpur Tentakel
// 15.03.25
//

#pragma once

#include <uil/debug/debug.hpp>

namespace uil {
    class Window;
}

namespace uil::debug {
    class FpsDebug final : public Debug<Window> {
    public:
        void exec(Window const&) const override;
    };
} // namespace uil::debug
