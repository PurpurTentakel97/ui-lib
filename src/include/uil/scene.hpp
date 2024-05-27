//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <uil/ui_element.hpp>
#include <uil/update_render_helper.hpp>
#include <vector>

class InputEvent;

namespace uil {
    class Scene : public UpdateRenderHelper {
    public:
        friend class SceneManager;

    private:
        std::vector<UIElement> m_elements{};

    protected:
        [[nodiscard]] virtual bool handle_event(InputEvent const& event);
        [[nodiscard]] virtual bool update();
        virtual void resize(cpt::Vec2_i resolution);
        virtual void render();

    public:
        Scene()                        = default;
        Scene(Scene const&)            = default;
        Scene(Scene&&)                 = default;
        Scene& operator=(Scene const&) = default;
        Scene& operator=(Scene&&)      = default;
        virtual ~Scene()               = default;

        void add(UIElement element);
        void add(std::vector<UIElement> element);
    };
} // namespace uil
