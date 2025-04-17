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
        Input m_input{};

    public:
        [[nodiscard]] static AppContext& instance();

        [[nodiscard]] Input_ref input();
        [[nodiscard]] Input_const_ref input() const;
    };

    using AppContext_ref      = AppContext&;
    using AppContext_cont_ref = AppContext const&;
} // namespace uil
