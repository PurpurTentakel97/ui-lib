//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <uil/alignment.hpp>
#include <raylib.h>
#include <uil/update_render_helper.hpp>

class InputEvent;

namespace uil {
    class UIElement : public UpdateRenderHelper {
    public:
        friend class Scene;

    private:
        Rectangle m_relative;
        Rectangle m_collider;
        Alignment m_alignment;

    protected:
        virtual bool handle_event(InputEvent const& event) = 0;
        virtual bool update();
        virtual void resize(cpt::Vec2_i resolution);
        virtual void render() = 0;

    public:
        UIElement(Rectangle relative, cpt::Vec2_i resolution, Alignment alignment);
        UIElement(UIElement const&)            = default;
        UIElement(UIElement&&)                 = default;
        UIElement& operator=(UIElement const&) = default;
        UIElement& operator=(UIElement&&)      = default;
        virtual ~UIElement()                   = default;
    };
} // namespace uil
