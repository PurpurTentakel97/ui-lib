//
// Purpur Tentakel
// 15.03.25
//

#include <string>
#include <uil/debug/debug_classes.hpp>
#include <uil/debug/debug_types.hpp>
#include <uil/global/app_context.hpp>

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
    void ColliderDrawDebug::exec([[maybe_unused]] Rectangle const* const collider) const {
#ifndef NDEBUG
        if (m_value) {
            DrawRectangleLinesEx(*collider, 2.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    void ColliderWithOffsetDrawDebug::exec([[maybe_unused]] ColliderWithOffsetDrawDebugData const* const collider_with_offset) const {
#ifndef NDEBUG
        if (m_value) {
            auto const collider = Rectangle{
                collider_with_offset->collider.x + collider_with_offset->offset.x,
                collider_with_offset->collider.y + collider_with_offset->offset.y,
                collider_with_offset->collider.width,
                collider_with_offset->collider.height,
            };
            DrawRectangleLinesEx(collider, 2.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------

namespace uil::debug {
    void MovementDrawDebug::exec([[maybe_unused]] MovementDrawDebugData const* const data) const {
#ifndef NDEBUG
        if (m_value) {
            auto const& resolution = AppContext::instance().resolution().resolution_vector();
            auto const start       = Vector2{ data->start.x * static_cast<float>(resolution.x),
                                        data->start.y * static_cast<float>(resolution.y) };
            auto const end = Vector2{ data->end.x * static_cast<float>(resolution.x),
                                      data->end.y * static_cast<float>(resolution.y) };
            DrawLineEx(start, end, 2.0f, WHITE);
        }
#endif
    }
} // namespace uil::debug

// ----------------------------------------
