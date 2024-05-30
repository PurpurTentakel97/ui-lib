//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/vec2.hpp>
#include <uil/resolution.hpp>
#include <uil/scene_manager.hpp>

namespace uil {
    class Window final {
    private:
        cpt::Vec2_i m_resolution_usize = { 100, 100 };
        Resolution m_resolution        = Resolution::CUSTOM;
        bool m_owner                   = false;
        SceneManager m_scene_manager{};
        cpt::usize m_fps = 60;
        bool m_draw_fps  = false;

    public:
        Window(cpt::Vec2_i resolution, char const* title);
        Window(Resolution resolution, char const* title);
        Window(Window const&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) noexcept;
        ~Window();

        [[nodiscard]] bool is_possible_resolution(Resolution resolution) const;
        [[nodiscard]] bool is_possible_resolution(cpt::Vec2_i resolution) const;

        void update();

        void set_resolution(Resolution resolution);
        void set_resolution(cpt::Vec2_i resolution);

        [[nodiscard]] Resolution resolution() const;
        [[nodiscard]] cpt::Vec2_i resolution_usize() const;

        void set_fps(cpt::usize fps);
        [[nodiscard]] cpt::usize fps() const;

        void set_draw_fps(bool draw);
        [[nodiscard]] bool draw_fps() const;
    };
} // namespace uil
