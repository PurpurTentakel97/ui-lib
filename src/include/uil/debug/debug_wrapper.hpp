//
// Purpur Tentakel
// 15.03.25
//

#pragma once

#include <uil/debug/debug_classes.hpp>

namespace uil::debug {
    struct WindowDebug final {
        FpsDrawDebug fps{};
    };
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    struct UIElementDebug final {
        ColliderDrawDebug collider{};
        MovementDrawDebug movement{};
    };
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    struct TextDebug final {
        ColliderWithOffsetDrawDebug line_collider{};
    };
} // namespace uil::debug

// ----------------------------------------
