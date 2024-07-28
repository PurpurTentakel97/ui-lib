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

    void Window::set_flag(ConfigFlags const flag, bool const active) {
        active ? SetWindowState(flag) : ClearWindowState(flag);
    }

    Window::Window(cpt::Vec2_i const resolution, char const* const title, WindowConfig config)
        : m_resolution{ resolution } {
        using FlagVec           = std::vector<std::pair<ConfigFlags, bool>>;
        auto constexpr set_flag = [](ConfigFlags const flag, bool const active) {
            active ? SetWindowState(flag) : ClearWindowState(flag);
        };
        auto constexpr set_flags = [](FlagVec const& flags) {
            for (auto const& f : flags) {
                set_flag(f.first, f.second);
            }
        };
        auto const pre = FlagVec{
            { ConfigFlags::FLAG_MSAA_4X_HINT,       config.msaa        },
            { ConfigFlags::FLAG_WINDOW_HIGHDPI,     config.high_dpi    },
            { ConfigFlags::FLAG_INTERLACED_HINT,    config.interlased  },
            { ConfigFlags::FLAG_WINDOW_TRANSPARENT, config.transparent },
        };
        auto const post = FlagVec{
            { ConfigFlags::FLAG_VSYNC_HINT,               config.v_sync            },
            { ConfigFlags::FLAG_FULLSCREEN_MODE,          config.fullscreen        },
            { ConfigFlags::FLAG_WINDOW_RESIZABLE,         config.resizable         },
            { ConfigFlags::FLAG_WINDOW_UNDECORATED,       config.undecorated       },
            { ConfigFlags::FLAG_WINDOW_HIDDEN,            config.hidden            },
            { ConfigFlags::FLAG_WINDOW_MINIMIZED,         config.minimized         },
            { ConfigFlags::FLAG_WINDOW_MAXIMIZED,         config.maximized         },
            { ConfigFlags::FLAG_WINDOW_UNFOCUSED,         config.unfocused         },
            { ConfigFlags::FLAG_WINDOW_TOPMOST,           config.top_most          },
            { ConfigFlags::FLAG_WINDOW_ALWAYS_RUN,        config.always_run        },
            { ConfigFlags::FLAG_WINDOW_MOUSE_PASSTHROUGH, config.mouse_passthrough },
            { ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE, config.borderless_window },
        };
        set_flags(pre);
        InitWindow(resolution.x, resolution.y, title);
        set_flags(post);
        m_font = LoadFont("assets/font.ttf");
    }

    Window::~Window() {
        CloseWindow();
    }

    void Window::set_vsync(bool const vsync) {
        set_flag(ConfigFlags::FLAG_VSYNC_HINT, vsync);
    }
    void Window::set_fullscreen(bool const fullscreen) {
        set_flag(ConfigFlags::FLAG_FULLSCREEN_MODE, fullscreen);
    }
    void Window::set_resizeable(bool const resizeable) {
        set_flag(ConfigFlags::FLAG_WINDOW_RESIZABLE, resizeable);
    }
    void Window::set_undecorated(bool const undecorated) {
        set_flag(ConfigFlags::FLAG_WINDOW_UNDECORATED, undecorated);
    }
    void Window::set_hidden(bool const hidden) {
        set_flag(ConfigFlags::FLAG_WINDOW_HIDDEN, hidden);
    }
    void Window::set_minimized(bool const minimized) {
        set_flag(ConfigFlags::FLAG_WINDOW_MINIMIZED, minimized);
    }
    void Window::set_maximized(bool const maximized) {
        set_flag(ConfigFlags::FLAG_WINDOW_MAXIMIZED, maximized);
    }
    void Window::set_unfocused(bool const unfocused) {
        set_flag(ConfigFlags::FLAG_WINDOW_UNFOCUSED, unfocused);
    }
    void Window::set_top_most(bool const top_most) {
        set_flag(ConfigFlags::FLAG_WINDOW_TOPMOST, top_most);
    }
    void Window::set_always_run(bool const always_run) {
        set_flag(ConfigFlags::FLAG_WINDOW_ALWAYS_RUN, always_run);
    }
    void Window::set_mouse_pathrough(bool const mouse_pathrough) {
        set_flag(ConfigFlags::FLAG_WINDOW_MOUSE_PASSTHROUGH, mouse_pathrough);
    }
    void Window::set_boderless(bool const boderless) {
        set_flag(ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE, boderless);
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
#ifndef NDEBUG
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

    bool Window::is_config_flag(ConfigFlags const flag) {
        return IsWindowState(flag);
    }

} // namespace uil
