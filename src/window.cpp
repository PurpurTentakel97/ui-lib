//
// Purpur Tentakel
// 30.05.24
//

#include <uil/global/app_context.hpp>
#include <raylib.h>
#include <uil/update_context.hpp>
#include <uil/window.hpp>

namespace uil {
    void Window::update_resolution() {
        auto& resolution = AppContext::instance().resolution();

        auto const update = [&](bool const resize = true) {
            m_resolution = resolution.resolution();
            m_scene_manager.resize();
            if (resize) {
                auto const is_fullscreen  = IsWindowFullscreen();
                if (is_fullscreen) {
                    ToggleFullscreen();
                }

                auto const resolution_vec = resolution.resolution_vector();
                SetWindowSize(resolution_vec.x, resolution_vec.y);
                auto const screen_resolution = vec_from_resolution(Resolution::SCREEN);
                SetWindowPosition(
                    (screen_resolution.x - resolution_vec.x) / 2,
                    (screen_resolution.y - resolution_vec.y) / 2
                );

                if (is_fullscreen) {
                    ToggleFullscreen();
                }
            }
        };

        if (IsWindowResized()) {
            resolution.set_resolution(Resolution::RESIZED);
            update(false);
            return;
        }

        if (m_resolution != resolution.resolution()) {
            update();
            return;
        }
    }

    UpdateContext Window::create_context() {
        // clang-format off
        return UpdateContext{
            GetMousePosition(),
            GetFrameTime(),
            m_scene_manager
        };
        // clang-format on
    }

    void Window::set_flag(ConfigFlags const flag, bool const active) {
        active ? SetWindowState(flag) : ClearWindowState(flag);
    }

    Window::Window(char const* const title, WindowConfig config) {
        using FlagVec           = std::vector<std::pair<ConfigFlags, bool>>;
        auto constexpr set_flag = [](ConfigFlags const flag, bool const active) {
            active ? SetWindowState(flag) : ClearWindowState(flag);
        };
        auto constexpr set_flags = [set_flag](FlagVec const& flags) {
            for (auto const& f : flags) {
                set_flag(f.first, f.second);
            }
        };
        auto const pre = FlagVec{
            { ConfigFlags::FLAG_MSAA_4X_HINT, config.msaa },
            { ConfigFlags::FLAG_WINDOW_HIGHDPI, config.high_dpi },
            { ConfigFlags::FLAG_INTERLACED_HINT, config.interlaced },
            { ConfigFlags::FLAG_WINDOW_TRANSPARENT, config.transparent },
        };
        auto const post = FlagVec{
            { ConfigFlags::FLAG_VSYNC_HINT, config.v_sync },
            { ConfigFlags::FLAG_FULLSCREEN_MODE, config.fullscreen },
            { ConfigFlags::FLAG_WINDOW_RESIZABLE, config.resizable },
            { ConfigFlags::FLAG_WINDOW_UNDECORATED, config.undecorated },
            { ConfigFlags::FLAG_WINDOW_HIDDEN, config.hidden },
            { ConfigFlags::FLAG_WINDOW_MINIMIZED, config.minimized },
            { ConfigFlags::FLAG_WINDOW_MAXIMIZED, config.maximized },
            { ConfigFlags::FLAG_WINDOW_UNFOCUSED, config.unfocused },
            { ConfigFlags::FLAG_WINDOW_TOPMOST, config.top_most },
            { ConfigFlags::FLAG_WINDOW_ALWAYS_RUN, config.always_run },
            { ConfigFlags::FLAG_WINDOW_MOUSE_PASSTHROUGH, config.mouse_passthrough },
            { ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE, config.borderless_window },
        };
        set_flags(pre);
        InitWindow(800, 600, title);
        set_flags(post);
    }

    Window::~Window() {
        CloseWindow();
    }

    SceneManager& Window::scene_manager() {
        return m_scene_manager;
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

    void Window::set_borderless(bool const borderless) {
        set_flag(ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE, borderless);
    }

    bool Window::is_config_flag(ConfigFlags const flag) {
        return IsWindowState(flag);
    }

    void Window::update() {
        update_resolution();
        AppContext::instance().sound().update();
        auto const context = create_context();

        // updating
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        update_resolution();
        [[maybe_unused]] auto const t1 = m_scene_manager.handle_input(context);
        [[maybe_unused]] auto const t2 = m_scene_manager.update(context);

        // rendering
        BeginDrawing();
        ClearBackground(BLACK);
        m_scene_manager.render(context);

        debug.fps.exec(nullptr);

        EndDrawing();
    }
} // namespace uil
