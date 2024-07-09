//
// Purpur Tentakel
// 06.07.24
//

#include <uil/ui_element.hpp>

namespace uil {
    void UIElement::update_relative() {
        m_relative = relative_from_collider(m_collider, m_resolution);
    }

    void UIElement::update_collider() {
        m_collider = collider_from_relative(m_relative, m_resolution);
    }

    UIElement::UIElement(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution)
        : m_resolution{ resolution },
          m_alignment{ alignment },
          m_relative{ aligned_position(relative, alignment) },
          m_collider{ collider_from_relative(m_relative, resolution) } { }

    void UIElement::resize(cpt::Vec2_i const& resolution) {
        m_resolution = resolution;
        m_collider   = collider_from_relative(m_relative, m_resolution);
    }

    void UIElement::set_relative_position(Vector2 const position) {
        m_relative.x = position.x;
        m_relative.y = position.y;
        m_relative   = aligned_position(m_relative, m_alignment);
        update_collider();
    }

    void UIElement::set_relative_size(Vector2 const size) {
        m_relative        = aligned_position_reversed(m_relative, m_alignment);
        m_relative.width  = size.x;
        m_relative.height = size.y;
        m_relative        = aligned_position(m_relative, m_alignment);
        update_collider();
    }

    void UIElement::set_relative(Rectangle const relative) {
        m_relative = aligned_position(relative, m_alignment);
        update_collider();
    }

    Rectangle UIElement::relative() const {
        return m_relative;
    }

    void UIElement::set_absolute_position(Vector2 const position) {
        m_collider.x = position.x;
        m_collider.y = position.y;
        m_collider   = aligned_position(m_collider, m_alignment);
        update_relative();
    }

    void UIElement::set_absolute_size(Vector2 const size) {
        m_collider        = aligned_position_reversed(m_collider, m_alignment);
        m_collider.width  = size.x;
        m_collider.height = size.y;
        m_collider        = aligned_position(m_collider, m_alignment);
        update_relative();
    }

    void UIElement::set_collider(Rectangle const collider) {
        m_collider = aligned_position(collider, m_alignment);
        update_relative();
    }

    Rectangle UIElement::collider() const {
        return m_collider;
    }

    void UIElement::set_alignment(Alignment const alignment) {
        m_relative  = aligned_position_reversed(m_relative, m_alignment);
        m_alignment = alignment;
        m_relative  = aligned_position(m_relative, m_alignment);
        update_collider();
    }

    Alignment UIElement::alignment() const {
        return m_alignment;
    }
} // namespace uil
