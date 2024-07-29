//
// Purpur Tentakel
// 28.07.24
//

#include <uil/context.hpp>

namespace uil {
    Context::Context(Vector2 const _mouse_position,
                     Font const* const _font,
                     cpt::Vec2_i const _resolution,
                     float const _delta_time)
        : mouse_position{ _mouse_position },
          font{ _font },
          resolution{ _resolution },
          delta_time{ _delta_time } { }
} // namespace uil
