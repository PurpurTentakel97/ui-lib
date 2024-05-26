//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <uil/helper_rect.hpp>
#include <cpt/vec2.hpp>
#include <uil/alignment.hpp>
#include <uil/update_render_helper.hpp>

class InputEvent;

namespace uil {
    class UIElement : public UpdateRenderHelper {
    public:
        friend class Scene;

    private:
        cpt::Rect_f m_relative;
        cpt::Rect_f m_collider;
        Alignment m_alignment;

    protected:
        virtual bool handle_event(InputEvent const& event) = 0;
        virtual bool update();
        virtual void resize(cpt::Vec2_i resolution);
        virtual void render() = 0;

    public:
        UIElement(cpt::Rect_f relative, cpt::Vec2_i resolution, Alignment alignment);
        UIElement(UIElement const&)            = default;
        UIElement(UIElement&&)                 = default;
        UIElement& operator=(UIElement const&) = default;
        UIElement& operator=(UIElement&&)      = default;
        virtual ~UIElement()                   = default;
    };
} // namespace uil
