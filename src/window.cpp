//
// Purpur Tentakel
// 30.05.24
//

#include <uil/context.hpp>
#include <raylib.h>
#include <string>
#include <uil/test_scene.hpp>
#include <uil/window.hpp>

namespace uil {
    void Window::check_resolution() const {
        if (IsWindowResized()) {
            auto const resolution = cpt::Vec2_i{ GetRenderWidth(), GetRenderHeight() };
            auto const context    = Context{ GetMousePosition(), &m_font, resolution };
            m_scene_manager.resize(context);
        }
    }

    Window::Window(cpt::Vec2_i const resolution, char const* const title) : m_resolution{ resolution } {
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
        auto const context = Context(GetMousePosition(), &m_font, m_resolution);

        // updating
        check_resolution();
        [[maybe_unused]] auto const t1 = m_scene_manager.check(context);
        [[maybe_unused]] auto const t2 = m_scene_manager.update(context);

        // rendering
        BeginDrawing();
        ClearBackground(BLACK);
        [[maybe_unused]] auto const t3 = m_scene_manager.render(context);
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
