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

    Window::~Window() {
        CloseWindow();
    }

    void Window::update() {
        BeginDrawing();
        ClearBackground(BLACK);

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
