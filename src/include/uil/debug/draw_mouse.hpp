//
// Purpur Tentakel
// 15.05.26
//

#pragma once

#include <uil/debug/basic.hpp>

namespace uil::debug {
    class DebugMouseDraw final: public DebugBase<void> {
    public:
        void exec(void const*) const override;
    };
}
