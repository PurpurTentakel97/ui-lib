//
// Purpur Tentakel
// 30.05.24
//

#pragma once
#include <cpt/vec2.hpp>
#include <uil/scene_manager.hpp>

namespace uil {
    struct Context;

    class Window final {
    private:
        bool m_owner    = true;
        bool m_draw_fps = false;
        cpt::Vec2_i m_resolution;
        SceneManager m_scene_manager{};
        Font m_font{};

        void update_resolution();
        [[nodiscard]] Context create_context() const;

    public:
        Window(cpt::Vec2_i resolution, char const* title);
        Window(Window const&)              = delete;
        Window(Window&& window)            = delete;
        Window& operator=(Window const&)   = delete;
        Window& operator=(Window&& window) = delete;
        ~Window();

        void update();

        void set_draw_fps(bool draw_fps);
        [[nodiscard]] bool draw_fps() const;

        void set_config_flag(ConfigFlags flag, bool enable);
        [[nodiscard]] bool is_config_flag(ConfigFlags flag) const;
    };
} // namespace uil
