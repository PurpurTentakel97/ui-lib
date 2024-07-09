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
        cpt::Vec2_i m_resolution;
        Alignment m_alignment;
        Rectangle m_relative{}; // m_relative needs to be initialized bevor m_collider
        Rectangle m_collider{}; // m_relative needs to be initialized bevor m_collider

        void update_relative();
        void update_collider();

    public:
        UIElement(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution);

        UIElement(UIElement const&)            = delete;
        UIElement(UIElement&&)                 = default;
        UIElement& operator=(UIElement const&) = delete;
        UIElement& operator=(UIElement&&)      = default;
        virtual ~UIElement()                   = default;

        // [[nodiscard]] virtual bool check(Vector2 mousePosition);
        // [[nodiscard]] virtual bool update();
        [[nodiscard]] virtual bool render(Font const* font) const = 0;
        virtual void resize(cpt::Vec2_i const& resolution);

        void set_relative_position(Vector2 position);
        void set_relative_size(Vector2 size);
        void set_relative(Rectangle relative);
        [[nodiscard]] Rectangle relative() const;

        void set_absolute_position(Vector2 position);
        void set_absolute_size(Vector2 size);
        void set_collider(Rectangle collider);
        [[nodiscard]] Rectangle collider() const;

        void set_alignment(Alignment alignment);
        [[nodiscard]] Alignment alignment() const;
    };
} // namespace uil
