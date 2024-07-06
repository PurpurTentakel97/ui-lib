//
// Purpur Tentakel
// 06.07.24
//

#include <uil/ui_element.hpp>

namespace uil {
    Rectangle UIElement::relative() const {
        return m_relative;
    }

    Rectangle UIElement::collider() const {
        return m_collider;
    }

    UIElement::UIElement(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution)
        : m_relative{ aligned_position(relative, alignment) },
          m_collider{ collider_from_relative(m_relative, resolution) } { }
} // namespace uil
