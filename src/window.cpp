//
// Purpur Tentakel
// 19.05.24
//

#include <raylib.h>
#include <uil/exception.hpp>
#include <uil/resolution.hpp>
#include <uil/window.hpp>

namespace uil {
    void Window::set_resolution_helper(Resolution const resolution) {
        if (resolution == Resolution::CUSTOM) {
            throw BadResolution("not able to set custom resolution with enum. use int overload instead");
        }
        if (not is_possible_resolution(resolution)) {
            throw BadResolution("not able to set resolution bigger than screen");
        }

        m_resolution       = resolution;
        m_resolution_usize = vec_from_resolution(m_resolution, m_resolution_usize);
        SetWindowSize(m_resolution_usize.x, m_resolution_usize.y);
    }

    void Window::set_resolution_helper(cpt::Vec2i const resolution) {
        if (not is_possible_resolution(resolution)) {
            throw BadResolution("not able to set resolution bigger than screen");
        }

        m_resolution       = Resolution::CUSTOM;
        m_resolution_usize = resolution;
        SetWindowSize(m_resolution_usize.x, m_resolution_usize.y);
    }

    Window::Window(cpt::Vec2i const resolution, char const* title) {
        m_resolution_usize = resolution;
        InitWindow(resolution.x, resolution.y, title);
        SetExitKey(0);
        SetTargetFPS(static_cast<int>(m_fps));
        m_owner = true;
    }

    Window::Window(Resolution const resolution, char const* title) {
        m_resolution       = resolution;
        m_resolution_usize = vec_from_resolution(m_resolution, m_resolution_usize);
        InitWindow(m_resolution_usize.x, m_resolution_usize.y, title);
        SetExitKey(0);
        SetTargetFPS(static_cast<int>(m_fps));
        m_owner = true;
    }

    Window::Window(Window&& other) noexcept {
        std::swap(m_resolution, other.m_resolution);
        std::swap(m_resolution_usize, other.m_resolution_usize);
        std::swap(m_owner, other.m_owner);
        std::swap(m_scene_manager, other.m_scene_manager);
        std::swap(m_fps, other.m_fps);
        std::swap(m_draw_fps, other.m_draw_fps);
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (this == std::addressof(other)) {
            return *this;
        }
        std::swap(m_resolution, other.m_resolution);
        std::swap(m_resolution_usize, other.m_resolution_usize);
        std::swap(m_owner, other.m_owner);
        std::swap(m_scene_manager, other.m_scene_manager);
        std::swap(m_fps, other.m_fps);
        std::swap(m_draw_fps, other.m_draw_fps);

        return *this;
    }

    Window::~Window() {
        if (m_owner) {
            CloseWindow();
        }
    }

    bool Window::is_possible_resolution(Resolution const resolution) const {
        auto const res = vec_from_resolution(resolution, m_resolution_usize);
        return is_possible_resolution(res);
    }

    bool Window::is_possible_resolution(cpt::Vec2i const resolution) const {
        auto const screen = vec_from_resolution(Resolution::SCREEN, m_resolution_usize);
        return resolution.x <= screen.x and resolution.y <= screen.y;
    }

    bool Window::should_close() {
        return WindowShouldClose();
    }

    void Window::update() {
        // update events
        // maybe resize here too
        m_scene_manager.update();

        BeginDrawing();
        m_scene_manager.render();
        EndDrawing();
    }

    Window& Window::set_resolution(Resolution const resolution) & {
        set_resolution_helper(resolution);
        return *this;
    }

    Window Window::set_resolution(Resolution const resolution) && {
        set_resolution_helper(resolution);
        return std::move(*this);
    }

    Window& Window::set_resolution(cpt::Vec2i const resolution) & {
        set_resolution_helper(resolution);
        return *this;
    }

    Window Window::set_resolution(cpt::Vec2i const resolution) && {
        set_resolution_helper(resolution);
        return std::move(*this);
    }

    Resolution Window::resolution() const {
        return m_resolution;
    }

    cpt::Vec2i Window::resolution_usize() const {
        return m_resolution_usize;
    }

    Window& Window::set_fps(cpt::usize const fps) & {
        m_fps = fps;
        SetTargetFPS(static_cast<int>(fps));
        return *this;
    }

    Window Window::set_fps(cpt::usize const fps) && {
        m_fps = fps;
        SetTargetFPS(static_cast<int>(fps));
        return std::move(*this);
    }

    cpt::usize Window::fps() const {
        return m_fps;
    }

    cpt::usize Window::current_fps() {
        return static_cast<cpt::usize>(GetFPS());
    }

    Window& Window::set_draw_fps(bool const draw) & {
        m_draw_fps = draw;
        return *this;
    }

    Window Window::set_draw_fps(bool const draw) && {
        m_draw_fps = draw;
        return std::move(*this);
    }

    cpt::usize Window::draw_fps() const {
        return m_draw_fps;
    }
} // namespace uil
