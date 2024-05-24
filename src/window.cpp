//
// Purpur Tentakel
// 19.05.24
//

#include <cassert>
#include <raylib.h>
#include <uil/exception.hpp>
#include <uil/window.hpp>

namespace uil {
    [[nodiscard]] cpt::Vec2i Window::int_from_resolution(Resolution const resolution) const {
        switch (resolution) {
            // 16:9
            case Resolution::UHD2: return { 7600, 4320 };
            case Resolution::_5K: return { 5120, 2160 };
            case Resolution::UHD1: return { 3840, 2162 };
            case Resolution::WQHD: return { 2560, 1440 };
            case Resolution::FULL_HD: return { 1920, 1080 };
            case Resolution::HD: return { 1280, 720 };

            // 21:9
            case Resolution::_5K_ULTRA_WIDE: return { 5120, 2460 };
            case Resolution::UWQHD: return { 3440, 1440 };
            case Resolution::UWHD: return { 2560, 1080 };

            // 4:3
            case Resolution::QXGA: return { 2048, 1536 };
            case Resolution::UXGA: return { 1600, 1200 };
            case Resolution::SXGA_Plus: return { 1400, 1050 };
            case Resolution::XGA_plus: return { 1152, 864 };
            case Resolution::XGA: return { 1024, 768 };
            case Resolution::SVGA: return { 800, 600 };
            case Resolution::PAL: return { 768, 576 };
            case Resolution::VGA: return { 640, 480 };


            case Resolution::SCREEN: {
                auto const screen{ GetCurrentMonitor() };
                auto const height{ GetMonitorHeight(screen) };
                auto const width{ GetMonitorWidth(screen) };

                return { width, height };
            }
            case Resolution::CUSTOM: return m_resolution_usize;
        }
        assert(false and "unecpected resolution in switch case");
        return { 100, 100 };
    }
    void Window::set_resolution_helper(Resolution const resolution) {
        if (resolution == Resolution::CUSTOM) {
            throw BadResolution("not able to set custom resolution with enum. use int overload instead");
        }
        if (not is_possible_resolution(resolution)) {
            throw BadResolution("not able to set resolution bigger than screen");
        }

        m_resolution       = resolution;
        m_resolution_usize = int_from_resolution(m_resolution);
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

    Window::Window(cpt::Vec2i resolution, char const* title) {
        m_resolution_usize = resolution;
        InitWindow(resolution.x, resolution.y, title);
        SetExitKey(0);
        m_owner = true;
    }

    Window::Window(Window&& other) noexcept {
        std::swap(m_resolution, other.m_resolution);
        std::swap(m_resolution_usize, other.m_resolution_usize);
        std::swap(m_owner, other.m_owner);
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (this == std::addressof(other)) {
            return *this;
        }
        std::swap(m_resolution, other.m_resolution);
        std::swap(m_resolution_usize, other.m_resolution_usize);
        std::swap(m_owner, other.m_owner);
        return *this;
    }

    Window::~Window() {
        if (m_owner) {
            CloseWindow();
        }
    }

    bool Window::is_possible_resolution(Resolution const resolution) const {
        auto const res = int_from_resolution(resolution);
        return is_possible_resolution(res);
    }

    bool Window::is_possible_resolution(cpt::Vec2i const resolution) const {
        auto const screen = int_from_resolution(Resolution::SCREEN);
        return resolution.x <= screen.x and resolution.y <= screen.y;
    }

    bool Window::should_close() const {
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

    Window& Window::set_fps(int const fps) & {
        SetTargetFPS(fps);
        return *this;
    }

    Window Window::set_fps(int const fps) && {
        SetTargetFPS(fps);
        return std::move(*this);
    }

    Resolution Window::resolution() const {
        return m_resolution;
    }

    cpt::Vec2i Window::resolution_usize() const {
        return m_resolution_usize;
    }


} // namespace uil
