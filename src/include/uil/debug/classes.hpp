//
// Purpur Tentakel
// 26.05.25
//

#pragma once

#include <uil/debug/basic.hpp>

namespace uil::debug {
    class FPSDraw final: public BasicDebug<void> {
    public:
        void exec(void const*) const override;
    };
}

namespace uil::debug {
    class RectangleDraw final: public BasicDebug<Rectangle> {
    public:
        void exec(Rectangle const*) const override;
    };
}
