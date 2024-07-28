//
// Purpur Tentakel
// 06.07.24
//

#include <uil/context.hpp>
#include <uil/element.hpp>
#include <uil/exception.hpp>
#include <uil/helper/vec.hpp>

namespace uil {
    void UIElement::update_relative() {
        m_relative = relative_from_collider(m_collider, m_resolution);
    }

    void UIElement::update_collider() {
        m_collider = collider_from_relative(m_relative, m_resolution);
    }

    bool UIElement::is_arriving(Vector2 const& distance) const {
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

    void UIElement::arriving() {
        m_relative.x = m_relative_destination.x;
        m_relative.y = m_relative_destination.y;
        update_collider();
        m_move_type = MoveType::None;
        on_arrived.invoke(*this);
        on_movement_stop.invoke(*this);
    }

    void UIElement::move(Vector2 const& relative_distance) {
        m_relative.x += relative_distance.x;
        m_relative.y += relative_distance.y;
        update_collider();
    }

    void UIElement::linear_time() {
        auto direction = m_relative_destination - m_relative_origin;
        direction *= GetFrameTime() / m_move_time;
        linear(direction);
    }

    void UIElement::linear_speed() {
        auto direction = normalize(m_relative_destination - m_relative_origin);
        direction *= GetFrameTime() * m_move_speed;
        linear(direction);
    }

    void UIElement::linear(Vector2 const& direction) {
        if (is_arriving(direction)) {
            arriving();
        } else {
            move(direction);
        }
    }

    void UIElement::fast_to_slow() {
        auto const distance  = m_relative_destination - m_relative_origin;
        auto const remaining = m_relative_destination - point_from_rect(m_relative);
        auto direction       = normalize(m_relative_destination - point_from_rect(m_relative));
        direction *= GetFrameTime() * m_move_speed * (magnitude(remaining) / magnitude(distance));
        if (magnitude(direction) < 0.000001f) {
            arriving();
        } else {
            move(direction);
        }
    }

    void UIElement::slow_to_fast() {
        auto const distance = m_relative_destination - m_relative_origin;
        auto already_moved  = magnitude(point_from_rect(m_relative) - m_relative_origin);
        already_moved       = already_moved > 0.001f ? already_moved : 0.001f;
        auto direction      = normalize(m_relative_destination - point_from_rect(m_relative));
        direction *= GetFrameTime() * m_move_speed * (already_moved / magnitude(distance));
        if (is_arriving(direction)) {
            arriving();
        } else {
            move(direction);
        }
    }

    void UIElement::constant() {
        auto const time     = GetFrameTime();
        auto const distance = m_move_direction * time * m_move_speed;
        move(distance);
    }

    cpt::Vec2_i UIElement::resolution() const {
        return m_resolution;
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

    void UIElement::set_render_collider_debug(bool const render) {
        m_render_collider = render;
    }

    bool UIElement::render_collider_debug() const {
        return m_render_collider;
    }

    bool UIElement::hovered() const {
        return m_hovered;
    }

    bool UIElement::is_moving() const {
        return m_move_type != MoveType::None;
    }

    void UIElement::move_to_linear_time(Vector2 const destination, float const time) {
        m_move_type            = MoveType::Linear_Time;
        m_relative_origin      = point_from_rect(m_relative);
        m_relative_destination = aligned_position(destination, size_from_rect(m_relative), m_alignment);
        m_move_time            = time;
        on_movement_start.invoke(*this);
    }

    void UIElement::move_to_linear_speed(Vector2 const destination, float const speed) {
        m_move_type            = MoveType::Linear_Speed;
        m_relative_origin      = point_from_rect(m_relative);
        m_relative_destination = aligned_position(destination, size_from_rect(m_relative), m_alignment);
        m_move_speed           = speed;
        on_movement_start.invoke(*this);
    }

    void UIElement::move_to_fast_to_slow(Vector2 const destination, float const speed) {
        m_move_type            = MoveType::Fast_To_Slow;
        m_relative_origin      = point_from_rect(m_relative);
        m_relative_destination = aligned_position(destination, size_from_rect(m_relative), m_alignment);
        m_move_speed           = speed;
        on_movement_start.invoke(*this);
    }

    void UIElement::move_to_slow_to_fast(Vector2 const destination, float const speed) {
        m_move_type            = MoveType::Slow_To_Fast;
        m_relative_origin      = point_from_rect(m_relative);
        m_relative_destination = aligned_position(destination, size_from_rect(m_relative), m_alignment);
        m_move_speed           = speed;
        on_movement_start.invoke(*this);
    }

    void UIElement::move_constant(Vector2 const direction, float const speed) {
        m_move_type      = MoveType::Constant;
        m_move_direction = normalize(direction);
        m_move_speed     = speed;
        on_movement_start.invoke(*this);
    }

    void UIElement::move_stop() {
        m_move_type = MoveType::None;
        on_movement_stop.invoke(*this);
    }

    bool UIElement::has_started_moving() const {
        return m_last_move_type == MoveType::None and m_move_type != MoveType::None;
    }

    bool UIElement::has_stopped_moving() const {
        return m_last_move_type != MoveType::None and m_move_type == MoveType::None;
    }

    bool UIElement::check(Context const& context) {
        m_last_move_type = m_move_type;
        m_hovered        = CheckCollisionPointRec(context.mouse_position, m_collider);
        on_check.invoke(*this);
        return true;
    }

    bool UIElement::update(Context const&) {
        switch (m_move_type) {
                // clang-format off
            case MoveType::None:                         break;
            case MoveType::Linear_Time:  linear_time();  break;
            case MoveType::Linear_Speed: linear_speed(); break;
            case MoveType::Slow_To_Fast: slow_to_fast(); break;
            case MoveType::Fast_To_Slow: fast_to_slow(); break;
            case MoveType::Constant:     constant();     break;
            default:
                throw BadMovementType("unexpected movement type while updating UIElement");
                // clang-format on
        }
        on_update.invoke(*this);
        return true;
    }
    bool UIElement::render(Context const&) const {
#ifdef _DEBUG
        if (m_render_collider) {
            DrawRectangleLinesEx(m_collider, 2.0f, WHITE);
        }
#endif
        on_draw.invoke(*this);
        return true;
    }

    void UIElement::resize(Context const& context) {
        m_resolution = context.resolution;
        m_collider   = collider_from_relative(m_relative, m_resolution);
        on_resize.invoke(*this);
    }
} // namespace uil
