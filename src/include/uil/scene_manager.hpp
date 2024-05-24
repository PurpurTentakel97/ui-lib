//
// Purpur Tentakel
// 14.05.24
//

#pragma once

#include <uil/scene.hpp>
#include <vector>

namespace uil {
    class SceneManager final {
    public:
        friend class Window;

    private:
        std::vector<Scene> m_scenes;

    protected:
        bool handle_event(InputEvent const& event);
        bool update();
        void resize(cpt::Vec2i resolution);
        void render();

    public:
    };
} // namespace uil
