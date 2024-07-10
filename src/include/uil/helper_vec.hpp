//
// Purpur Tentakel
// 10.07.24
//

#pragma once
#include <raylib.h>

namespace uil {
    [[nodiscard]] float magnitude(Vector2 const& vec);

    [[nodiscard]] Vector2 normalize(Vector2 const& vec);
} // namespace uil
