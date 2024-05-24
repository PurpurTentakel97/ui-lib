//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/Vec2.hpp>
#include <uil/resolution.hpp>
#include <uil/scene_manager.hpp>
#include <utility>

namespace uil {
    class Window final {
    private:
        cpt::Vec2i m_resolution_usize = { 100, 100 };
        Resolution m_resolution       = Resolution::CUSTOM;
        bool m_owner                  = false;
        SceneManager m_scene_manager{};
        cpt::usize m_fps = 60;
        bool m_draw_fps  = false;

        void set_resolution_helper(Resolution resolution);
        void set_resolution_helper(cpt::Vec2i resolution);

    public:
        Window(cpt::Vec2i resolution, char const* title);
        Window(Resolution resolution, char const* title);
        Window(Window const&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) noexcept;
        ~Window();

        [[nodiscard]] bool is_possible_resolution(Resolution resolution) const;
        [[nodiscard]] bool is_possible_resolution(cpt::Vec2i resolution) const;

        [[nodiscard]] static bool should_close();

        void update();

        Window& set_resolution(Resolution resolution) &;
        Window set_resolution(Resolution resolution) &&;
        Window& set_resolution(cpt::Vec2i resolution) &;
        Window set_resolution(cpt::Vec2i resolution) &&;

        [[nodiscard]] Resolution resolution() const;
        [[nodiscard]] cpt::Vec2i resolution_usize() const;

        Window& set_fps(cpt::usize fps) &;
        Window set_fps(cpt::usize fps) &&;

        [[nodiscard]] cpt::usize fps() const;
        [[nodiscard]] static cpt::usize current_fps();

        Window& set_draw_fps(bool draw) &;
        Window set_draw_fps(bool draw) &&;

        [[nodiscard]] cpt::usize draw_fps() const;
    };

} // namespace uil
