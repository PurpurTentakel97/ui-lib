//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include "callback.hpp"
#include <raylib.h>
#include <uil/alignment.hpp>
#include <uil/helper_rect.hpp>

namespace uil {
    class UIElement {
    private:
        enum class MoveType {
            None,
            Linear_Time,  // moves linear to a certain point in a certain time
            Linear_Speed, // moves linear to a certain point in a certain speed
            Slow_To_Fast, // getting faster while moving to a certain point
            Fast_To_Slow, // getting slower while moving to a certain point
            Constant,     // moves at a constant speed until it gets stoppt manualy
        };

        // basic
        cpt::Vec2_i m_resolution;
        Alignment m_alignment;
        Rectangle m_relative{}; // m_relative needs to be initialized bevor m_collider
        Rectangle m_collider{}; // m_relative needs to be initialized bevor m_collider
        bool m_render_collider = false;

        // movement
        MoveType m_move_type      = MoveType::None;
        MoveType m_last_move_type = MoveType::None;
        float m_move_speed{};
        float m_move_time{};
        Vector2 m_relative_origin{};
        Vector2 m_relative_destination{};
        Vector2 m_move_direction{};

        void update_relative();
        void update_collider();

        [[nodiscard]] bool is_arriving(Vector2 const& distance) const;
        void arriving();

        void move(Vector2 const& relative_distance);
        void linear_time();
        void linear_speed();
        void linear(Vector2 const& direction);
        void fast_to_slow();
        void slow_to_fast();
        void constant();


    public:
        Callback<UIElement&> on_movement_start{};
        Callback<UIElement&> on_movement_stop{};
        Callback<UIElement&> on_arrived{};
        Callback<UIElement&> on_check{};
        Callback<UIElement&> on_update{};
        Callback<UIElement const&> on_draw{};
        Callback<UIElement&> on_resize{};


        UIElement(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution);

        UIElement(UIElement const&)            = delete;
        UIElement(UIElement&&)                 = default;
        UIElement& operator=(UIElement const&) = delete;
        UIElement& operator=(UIElement&&)      = default;
        virtual ~UIElement()                   = default;

        // basic
        void set_relative_position(Vector2 position);
        void set_relative_size(Vector2 size);
        void set_relative(Rectangle relative);
        [[nodiscard]] Rectangle relative() const;
        [[nodiscard]] Rectangle relative_aligned() const;

        void set_absolute_position(Vector2 position);
        void set_absolute_size(Vector2 size);
        void set_collider(Rectangle collider);
        [[nodiscard]] Rectangle collider() const;
        [[nodiscard]] Rectangle collider_aligned() const;

        void set_alignment(Alignment alignment);
        [[nodiscard]] Alignment alignment() const;

        void set_render_collider(bool render);
        [[nodiscard]] bool render_collider() const;

        // movement
        [[nodiscard]] bool is_moving() const;
        void move_to_linear_time(Vector2 destination, float time);
        void move_to_linear_speed(Vector2 destination, float speed);
        void move_to_fast_to_slow(Vector2 destination, float speed);
        void move_to_slow_to_fast(Vector2 destination, float speed);
        void move_constant(Vector2 direction, float speed);
        void move_stop();

        [[nodiscard]] bool has_started_moving() const;
        [[nodiscard]] bool has_stopped_moving() const;

        // polymorphic
        [[nodiscard]] virtual bool check(Vector2 const& mousePosition);
        [[nodiscard]] virtual bool update();
        [[nodiscard]] virtual bool render(Font const* font) const;
        virtual void resize(cpt::Vec2_i const& resolution);
    };
} // namespace uil
