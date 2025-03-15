//
// Purpur Tentakel
// 15.03.25
//

#pragma once

#include <cpt/vec2.hpp>
#include <raylib.h>
#include <uil/debug/debug.hpp>

namespace uil {
    class Window;
}

namespace uil::debug {
    class FpsDrawDebug final : public Debug<void> {
    public:
        void exec(void const*) const override;
    };
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    class ColliderDrawDebug final : public Debug<Rectangle> {
    public:
        void exec(Rectangle const*) const override;
    };
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    struct ColliderWithOffsetDrawDebugData;
    class ColliderWithOffsetDrawDebug final : public Debug<ColliderWithOffsetDrawDebugData> {
    public:
        void exec(ColliderWithOffsetDrawDebugData const*) const override;
    };
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    struct MovementDrawDebugData;
    class MovementDrawDebug final : public Debug<MovementDrawDebugData> {
    public:
        void exec(MovementDrawDebugData const*) const override;
    };
} // namespace uil::debug

// ----------------------------------------
