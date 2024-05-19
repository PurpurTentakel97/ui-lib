//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <uil/Resolution.hpp>
#include <utility>

namespace uil {
    class Window final {
    public:
        using resolution_ty = std::pair<int, int>;

    private:
        bool m_owner                     = false;
        resolution_ty m_resolution_usize = { 100, 100 };
        Resolution m_resolution          = Resolution::CUSTOM;

        [[nodiscard]] resolution_ty int_from_resolution(Resolution resolution) const;

        void set_resolution_helper(Resolution resolution);
        void set_resolution_helper(int width, int height);

    public:
        Window();
        Window(Window const&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) noexcept;
        ~Window();

        [[nodiscard]] bool is_possible_resolution(Resolution resolution) const;
        [[nodiscard]] bool is_possible_resolution(int width, int height) const;

        [[nodiscard]] bool should_close() const;

        void update();

        Window& set_resolution(Resolution resolution) &;
        Window set_resolution(Resolution resolution) &&;
        Window& set_resolution(int width, int height) &;
        Window set_resolution(int width, int height) &&;

        Window& set_fps(int fps);
    };

} // namespace uil
