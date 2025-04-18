//
// Purpur Tentakel
// 30.03.25
//

#pragma once

#include <uil/global/input.hpp>
#include <uil/global/sound.hpp>

namespace uil {
    class Window;
}

namespace uil {

    class AppContext final {
    private:
        InputManager m_input{};
        SoundManager m_sound{};

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

        [[nodiscard]] SoundManager& sound();
        [[nodiscard]] SoundManager const& sound() const;
    };
} // namespace uil
