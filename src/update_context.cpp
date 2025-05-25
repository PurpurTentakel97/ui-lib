//
// Purpur Tentakel
// 28.07.24
//

#include <uil/update_context.hpp>

namespace uil {
    UpdateContext::UpdateContext(Vector2 const _mouse_position,
                                 Font const* const _font,
                                 float const _delta_time,
                                 SceneManager& _scene_manager)
        : mouse_position{ _mouse_position },
          font{ _font },
          delta_time{ _delta_time },
          scene_manager{ _scene_manager } { }
} // namespace uil
