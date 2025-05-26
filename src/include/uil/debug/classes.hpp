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
