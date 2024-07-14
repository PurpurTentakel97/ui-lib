//
// Purpur Tentakel
// 06.07.24
//

#include "uil/exception.hpp"
#include "uil/helper_vec.hpp"
#include <uil/ui_element.hpp>

namespace uil {
    void UIElement::update_relative() {
        m_relative = relative_from_collider(m_collider, m_resolution);
    }

    void UIElement::update_collider() {
        m_collider = collider_from_relative(m_relative, m_resolution);
    }

    bool UIElement::arriving(Vector2 const& distance) const {
        auto arrived_x = false;
        if (m_relative_origin.x <= m_relative_destination.x) {
            arrived_x = m_relative.x + distance.x >= m_relative_destination.x;
        } else {
            arrived_x = m_relative.x + distance.x <= m_relative_destination.x;
        }
        auto arrived_y = false;
        if (m_relative_origin.y <= m_relative_destination.y) {
            arrived_y = m_relative.y + distance.y >= m_relative_destination.y;
        } else {
            arrived_y = m_relative.y + distance.y <= m_relative_destination.y;
        }

        return arrived_x and arrived_y;
    }

    void UIElement::move(Vector2 const& relative_distance) {
        m_relative.x += relative_distance.x;
        m_relative.y += relative_distance.y;
        update_collider();
    }

    void UIElement::linear() {
        auto direction = normalize(m_relative_destination - m_relative_origin);
        direction *= GetFrameTime() * m_move_speed;
        if (arriving(direction)) {
            m_relative.x = m_relative_destination.x;
            m_relative.y = m_relative_destination.y;
            update_collider();
            m_move_type = MoveType::None;
        } else {
            move(direction);
        }
    }

    void UIElement::constant() {
        auto const time     = GetFrameTime();
        auto const distance = m_move_direction * time * m_move_speed;
        move(distance);
    }

    UIElement::UIElement(Rectangle const relative, Alignment const alignment, cpt::Vec2_i const resolution)
        : m_resolution{ resolution },
          m_alignment{ alignment },
          m_relative{ aligned_position(relative, alignment) },
          m_collider{ collider_from_relative(m_relative, resolution) } { }

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
        return aligned_position_reversed(m_relative, m_alignment);
    }

    Rectangle UIElement::relative_aligned() const {
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
        return aligned_position_reversed(m_collider, m_alignment);
    }

    Rectangle UIElement::collider_aligned() const {
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

    bool UIElement::is_moving() const {
        return m_move_type != MoveType::None;
    }

    void UIElement::move_to_linear(Vector2 const destination, float const speed) {
        m_move_type            = MoveType::Linear;
        m_relative_origin      = point_from_rect(m_relative);
        m_relative_destination = destination;
        m_move_speed           = speed;
    }

    void UIElement::move_to_fast_to_slow(Vector2 const destination, float const speed) {
        m_move_type            = MoveType::Fast_To_Slow;
        m_relative_origin      = { relative().x, relative().y };
        m_relative_destination = destination;
        m_move_speed           = speed;
    }

    void UIElement::move_to_slow_to_fast(Vector2 const destination, float const speed) {
        m_move_type            = MoveType::Slow_To_Fast;
        m_relative_origin      = { relative().x, relative().y };
        m_relative_destination = destination;
        m_move_speed           = speed;
    }

    void UIElement::move_constant(Vector2 const direction, float const speed) {
        m_move_type      = MoveType::Constant;
        m_move_direction = normalize(direction);
        m_move_speed     = speed;
    }

    void UIElement::move_stop() {
        m_move_type = MoveType::None;
    }

    bool UIElement::check(Vector2 const&) {
        return true;
    }

    bool UIElement::update() {
        switch (m_move_type) {
                // clang-format off
            case MoveType::None:                         break;
            case MoveType::Linear:       linear();       break;
            case MoveType::Slow_To_Fast: /*slow_to_fast();*/ break;
            case MoveType::Fast_To_Slow: /*fast_to_slow();*/ break;
            case MoveType::Constant:     constant();     break;
            default:
                throw BadMovementType("unexpected movement type while updating UIElement");
                // clang-format on
        }
        return true;
    }

    void UIElement::resize(cpt::Vec2_i const& resolution) {
        m_resolution = resolution;
        m_collider   = collider_from_relative(m_relative, m_resolution);
    }
} // namespace uil
