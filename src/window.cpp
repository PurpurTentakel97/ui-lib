//
// Purpur Tentakel
// 30.05.24
//

#include <raylib.h>
#include <string>
#include <uil/test_scene.hpp>
#include <uil/window.hpp>

namespace uil {
    Window::Window(cpt::Vec2_i const resolution, char const* const title) {
        InitWindow(resolution.x, resolution.y, title);
        m_font = LoadFont("../default_assets/font.ttf"); // @TODO Move this into a extra data data member
        m_scene_manager.add_scene(std::make_unique<TestScene>(resolution));
    }

    Window::~Window() {
        if (m_owner) {
            CloseWindow();
        }
    }

    void Window::update() {
        // updating
        [[maybe_unused]] auto const t1 = m_scene_manager.check(GetMousePosition());
        [[maybe_unused]] auto const t2 = m_scene_manager.update();

        // rendering
        BeginDrawing();
        ClearBackground(BLACK);
        [[maybe_unused]] auto const t3 = m_scene_manager.render(&m_font);
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

    void Window::set_config_flag(ConfigFlags const flag, bool const enable) {
        if (enable) {
            SetWindowState(flag);
        } else {
            ClearWindowState(flag);
        }
    }

    bool Window::is_config_flag(ConfigFlags const flag) const {
        return IsWindowState(flag);
    }

} // namespace uil
