//
// Purpur Tentakel
// 23.05.24
//

#include <uil/ui_element.hpp>

namespace uil {
    UIElement::UIElement(cpt::Vec2f pos, cpt::Vec2f size, cpt::Vec2i resolution, Alignment alignment)
        : m_pos{ pos },
          m_size{ size },
          m_collider{ 0.0f, 0.0f, 0.0f, 0.0f },
          m_alignment{ alignment } {
        m_pos      = aligned_position(m_pos, m_size, m_alignment);
        m_collider = collider_from_relative(pos, size, resolution);
    }
} // namespace uil
