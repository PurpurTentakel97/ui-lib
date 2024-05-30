//
// Purpur Tentakel
// 30.05.24
//

#pragma once
#include <cpt/vec2.hpp>

class SceneManager;
class PopupManager;
class EventManager;
class AudioPlayer;
class UIElement;

namespace uil {
    class Window final {
    private:
        bool m_owner    = true;
        bool m_draw_fps = false;

    public:
        Window(cpt::Vec2_i resolution, char const* title);
        Window(Window const&) = delete;
        Window(Window&& window) noexcept;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&& window) noexcept;
        ~Window();

        void update();

        void set_draw_fps(bool draw_fps);
        [[nodiscard]] bool draw_fps() const;
    };
} // namespace uil
