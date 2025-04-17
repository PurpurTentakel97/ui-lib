//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <uil/global/input.hpp>

namespace uil {
    class Window;
}

namespace uil {

    class AppContext final {
    private:
        InputManager m_input{};

    public:
        AppContext()                             = default;
        AppContext(AppContext const&)            = delete;
        AppContext(AppContext&&)                 = delete;
        AppContext& operator=(AppContext const&) = delete;
        AppContext& operator=(AppContext&&)      = delete;
        ~AppContext()                            = default;

        [[nodiscard]] static AppContext& instance();

        [[nodiscard]] InputManager& input();
        [[nodiscard]] InputManager const& input() const;
    };
} // namespace uil
