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

        [[nodiscard]] Input& input();
        [[nodiscard]] Input const& input() const;
    };
} // namespace uil
