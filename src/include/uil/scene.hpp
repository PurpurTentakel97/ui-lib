//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/Vec2.hpp>
#include <vector>

class UIElement;
class InputEvent;

namespace uil {
    class Scene {
    private:
        std::vector<UIElement> m_elements{};

    protected:
        virtual bool handle_event(InputEvent const& event);
        virtual bool update();
        virtual void resize(cpt::Vec2i resolution);
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
