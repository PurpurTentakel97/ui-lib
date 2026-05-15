//
// Purpur Tentakel
// 15.05.26
//

#pragma once

#include <uil/debug/basic.hpp>

namespace uil::debug {
    class MouseDraw final: public BasicDebug<void> {
    public:
        void exec(void const*) const override;
    };
}
