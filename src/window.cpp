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
        m_scene_manager.add_scene(std::make_unique<TestScene>(resolution));
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

        m_scene_manager.render();

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
