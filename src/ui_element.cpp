//
// Purpur Tentakel
// 23.05.24
//

#include <uil/ui_element.hpp>

namespace uil {
    bool UIElement::update() {
        // TODO: implement some moving stuff here
        return true;
    }

    void UIElement::resize(cpt::Vec2_i const resolution) {
        m_collider = collider_from_relative(m_relative, resolution);
    }

    UIElement::UIElement(cpt::Rect_f const relative, cpt::Vec2_i const resolution, Alignment const alignment)
        : m_relative{ relative },
          m_collider{ 0.0f, 0.0f, 0.0f, 0.0f },
          m_alignment{ alignment } {
        m_relative = aligned_position(m_relative, m_alignment);
        m_collider = collider_from_relative(m_relative, resolution);
    }
} // namespace uil
