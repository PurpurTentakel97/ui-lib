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
        Rectangle m_relative{}; // m_relative needs to be initialized bevor m_collider
        Rectangle m_collider{}; // m_relative needs to be initialized bevor m_collider

    protected:
        [[nodiscard]] Rectangle relative() const;
        [[nodiscard]] Rectangle collider() const;

    public:
        UIElement(Rectangle relative, Alignment alignment, cpt::Vec2_i resolution);

        UIElement(UIElement const&)            = delete;
        UIElement(UIElement&&)                 = delete;
        UIElement& operator=(UIElement const&) = delete;
        UIElement& operator=(UIElement&&)      = delete;
        virtual ~UIElement()                   = default;

        // [[nodiscard]] virtual bool check(Vector2 mousePosition);
        // [[nodiscard]] virtual bool update();
        [[nodiscard]] virtual bool render() const = 0;
        // virtual void resize();
    };
} // namespace uil
