//
// Purpur Tentakel
// 30.05.24
//

#include <raylib.h>
#include <string>
#include <uil/context.hpp>
#include <uil/window.hpp>

namespace uil {
    void Window::update_resolution() {
        if (IsWindowResized()) {
            m_resolution = cpt::Vec2_i{ GetRenderWidth(), GetRenderHeight() };
            m_scene_manager.resize(create_context());
        }
    }

    Context Window::create_context() const {
        return Context{ GetMousePosition(), &m_font, m_resolution };
    }

    Window::Window(cpt::Vec2_i const resolution, char const* const title) : m_resolution{ resolution } {
        InitWindow(resolution.x, resolution.y, title);
        m_font = LoadFont("assets/font.ttf");
    }

    Window::~Window() {
        CloseWindow();
    }

    void Window::update() {
        auto const context = create_context();

        // updating
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        update_resolution();
        [[maybe_unused]] auto const t1 = m_scene_manager.check(context);
        [[maybe_unused]] auto const t2 = m_scene_manager.update(context);

        // rendering
        BeginDrawing();
        ClearBackground(BLACK);
        [[maybe_unused]] auto const t3 = m_scene_manager.render(context);
#ifdef _DEBUG
        if (m_draw_fps) {
            DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 50, WHITE);
        }
#endif
        EndDrawing();
    }

    void Window::set_draw_fps_debug(bool const draw_fps) {
        m_draw_fps = draw_fps;
    }

    bool Window::draw_fps_debug() const {
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
