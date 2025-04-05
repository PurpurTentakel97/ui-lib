//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <uil/global/input.hpp>

namespace uil {
    class Window;
}

namespace uil::global {

    class AppContext final {
    private:
        friend class uil::Window;

        InputManager m_input{};

        void reset();

    public:
        [[nodiscard]] static AppContext& instance();

        [[nodiscard]] InputManager& input();
        [[nodiscard]] InputManager const& input() const;
    };
} // namespace uil::global
