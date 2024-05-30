//
// Purpur Tentakel
// 30.05.24
//

#include <raylib.h>
#include <string>
#include <uil/window.hpp>

namespace uil {

    Window::Window(cpt::Vec2_i const resolution, char const* const title) {
        InitWindow(resolution.x, resolution.y, title);
    }

    Window::Window(Window&& window) noexcept : m_owner{ false } {
        std::swap(m_owner, window.m_owner);
        std::swap(m_draw_fps, window.m_draw_fps);
    }

    Window& Window::operator=(Window&& window) noexcept {
        m_owner = false;
        std::swap(m_owner, window.m_owner);
        std::swap(m_draw_fps, window.m_draw_fps);
        return *this;
    }

    Window::~Window() {
        if (m_owner) {
            CloseWindow();
        }
    }

    void Window::update() {
        // handle events m_scene_manger.handle_event(event, event_manager, auto_player, vec2 mouse_position);
        // check m_scene_manager.check(event_manager, audio_player, vec2 mouse_position);
        // update m_scene_manager.update();

        BeginDrawing();
        ClearBackground(BLACK);
        // render

        if (m_draw_fps) {
            DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 50, WHITE);
        }

        EndDrawing();
    }

    void Window::set_draw_fps(bool const draw_fps) {
        m_draw_fps = draw_fps;
    }

    bool Window::draw_fps() const {
        return m_draw_fps;
    }

} // namespace uil
