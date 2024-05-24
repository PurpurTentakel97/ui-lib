//
// Purpur Tentakel
// 23.05.24
//

#include <uil/ui_element.hpp>

namespace uil {
    UIElement::UIElement(Rect relative, cpt::Vec2i resolution, Alignment alignment)
        : m_relative{ relative },
          m_collider{ 0.0f, 0.0f, 0.0f, 0.0f },
          m_alignment{ alignment } {
        m_relative      = aligned_position(m_relative, m_alignment);
        m_collider = collider_from_relative(m_relative, resolution);
    }
} // namespace uil
