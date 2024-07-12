//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <raylib.h>
#include <uil/alignment.hpp>
#include <uil/helper_rect.hpp>

namespace uil {
    class UIElement {
    private:
        enum class MoveType {
            None,
            Linear,       // moves linear to a certain point
            Slow_To_Fast, // getting faster while moving to a certain point
            Fast_To_Slow, // getting slower while moving to a certain point
            Constant,     // moves at a constant speed until it gets stoppt manualy
        };

        // basic
        cpt::Vec2_i m_resolution;
        Alignment m_alignment;
        Rectangle m_relative{}; // m_relative needs to be initialized bevor m_collider
        Rectangle m_collider{}; // m_relative needs to be initialized bevor m_collider

        // movement
        MoveType m_move_type = MoveType::None;
        float m_move_speed{};
        Vector2 m_relative_origin{};
        Vector2 m_relative_destination{};
        Vector2 m_move_direction{};

        void update_relative();
        void update_collider();

        void move(Vector2 const& relative_distance);
        void linear();
        void fast_to_slow();
        void slow_to_fast();
        void constant();


    public:
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

        // movement
        void move_to_linear(Vector2 destination, float speed);
        void move_to_fast_to_slow(Vector2 destination, float speed);
        void move_to_slow_to_fast(Vector2 destination, float speed);
        void move_constant(Vector2 direction, float speed);
        void move_stop();

        // polymorphic
        [[nodiscard]] virtual bool check(Vector2 const& mousePosition);
        [[nodiscard]] virtual bool update();
        [[nodiscard]] virtual bool render(Font const* font) const = 0;
        virtual void resize(cpt::Vec2_i const& resolution);
    };
} // namespace uil
