//
// Purpur Tentakel
// 15.05.26
//

#pragma once

#include <uil/debug/basic.hpp>

struct Rectangle;

namespace uil::debug {
    class RectangleDraw final : public BasicDebug<Rectangle> {
    public:
        void exec(Rectangle const*) const override;
    };
} // namespace uil::debug
