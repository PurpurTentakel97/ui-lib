//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/Vec2.hpp>
#include <uil/Utils.hpp>
#include <uil/update_render_helper.hpp>
#include <uil/alignment.hpp>

class InputEvent;

namespace uil {
    class UIElement : public UpdateRenderHelper {
    public:
        friend class Scene;

    private:
        cpt::Vec2f m_pos, m_size;
        Rect m_collider;

    protected:
        virtual bool handle_event(InputEvent const& event);
        virtual bool update();
        virtual void resize(cpt::Vec2i resolution);
        virtual void render();

    public:
        UIElement(cpt::Vec2f pos, cpt::Vec2f size, cpt::Vec2i resolution, Alignment alignment);
        UIElement(UIElement const&)            = default;
        UIElement(UIElement&&)                 = default;
        UIElement& operator=(UIElement const&) = default;
        UIElement& operator=(UIElement&&)      = default;
        virtual ~UIElement()                   = default;
    };
} // namespace uil
