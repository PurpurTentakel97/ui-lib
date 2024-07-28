//
// Purpur Tentakel
// 30.05.24
//

#pragma once
#include <cpt/vec2.hpp>
#include <uil/scene_manager.hpp>

namespace uil {
    struct Context;

    struct WindowConfig final {
        bool v_sync            = false;
        bool fullscreen        = false;
        bool resizable         = false;
        bool undecorated       = false;
        bool hidden            = false;
        bool minimized         = false;
        bool maximized         = false;
        bool unfocused         = false;
        bool top_most          = false;
        bool always_run        = false;
        bool transparent       = false;
        bool high_dpi          = false;
        bool mouse_passthrough = false;
        bool borderless_window = false;
        bool msaa              = false;
        bool interlased        = false;
    };

    class Window final {
    private:
        bool m_draw_fps = true;
        cpt::Vec2_i m_resolution;
        SceneManager m_scene_manager{};
        Font m_font{};

        void update_resolution();
        [[nodiscard]] Context create_context() const;

    public:
        Window(cpt::Vec2_i resolution, char const* title, WindowConfig config);
        Window(Window const&)              = delete;
        Window(Window&& window)            = delete;
        Window& operator=(Window const&)   = delete;
        Window& operator=(Window&& window) = delete;
        ~Window();

        template<std::derived_from<Scene> T, typename... Args>
        T& emplace_scene(Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return m_scene_manager.emplace_scene<T>(m_resolution, args...);
        }

        void update();

        void set_draw_fps_debug(bool draw_fps);
        [[nodiscard]] bool draw_fps_debug() const;

        [[nodiscard]] static bool is_config_flag(ConfigFlags flag);
    };
} // namespace uil
