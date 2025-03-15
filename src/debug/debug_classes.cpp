//
// Purpur Tentakel
// 15.03.25
//

#include <string>
#include <uil/debug/debug_classes.hpp>
#include <uil/window.hpp>
#include <uil/debug/debug_types.hpp>

namespace uil::debug {
    void FpsDrawDebug::exec(void const* const) const {
#ifndef NDEBUG
        if (m_value) {
            DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 50, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    void ColliderDrawDebug::exec(Rectangle const* const collider) const {
#ifndef NDEBUG
        if (m_value) {
            DrawRectangleLinesEx(*collider, 2.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    void ColliderWithOffsetDrawDebug::exec(std::pair<Vector2, Rectangle> const* const collider_with_offset) const {
#ifndef NDEBUG
        if (m_value) {
            auto const collider = Rectangle{
                collider_with_offset->first.x + collider_with_offset->second.x,
                collider_with_offset->first.y + collider_with_offset->second.y,
                collider_with_offset->second.width,
                collider_with_offset->second.height,
            };
            DrawRectangleLinesEx(collider, 2.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    void MovementDrawDebug::exec(MovementDrawDebugData const* const data) const {
#ifndef NDEBUG
        if (m_value) {
            auto const start = Vector2{ data->start.x * static_cast<float>(data->resolution.x),
                                        data->start.y * static_cast<float>(data->resolution.y) };
            auto const end   = Vector2{ data->end.x * static_cast<float>(data->resolution.x),
                                      data->end.y * static_cast<float>(data->resolution.y) };
            DrawLineEx(start, end, 2.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------
