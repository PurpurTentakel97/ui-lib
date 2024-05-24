//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <cpt/Vec2.hpp>
#include <uil/resolution.hpp>
#include <utility>

namespace uil {
    class Window final {
    private:
        bool m_owner                  = false;
        cpt::Vec2i m_resolution_usize = { 100, 100 };
        Resolution m_resolution       = Resolution::CUSTOM;

        [[nodiscard]] cpt::Vec2i int_from_resolution(Resolution resolution) const;

        void set_resolution_helper(Resolution resolution);
        void set_resolution_helper(cpt::Vec2i resolution);

    public:
        Window(cpt::Vec2i resolution, char const* title);
        Window(Window const&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) noexcept;
        ~Window();

        [[nodiscard]] bool is_possible_resolution(Resolution resolution) const;
        [[nodiscard]] bool is_possible_resolution(cpt::Vec2i resolution) const;

        [[nodiscard]] bool should_close() const;

        void start_frame();
        void update();
        void end_frame();

        Window& set_resolution(Resolution resolution) &;
        Window set_resolution(Resolution resolution) &&;
        Window& set_resolution(cpt::Vec2i resolution) &;
        Window set_resolution(cpt::Vec2i resolution) &&;

        // [[nodiscard]] Resolution resolution() const;
        // [[nodiscard]] cpt::Vec2i resolution() const;

        Window& set_fps(int fps) &;
        Window set_fps(int fps) &&;
    };

} // namespace uil
