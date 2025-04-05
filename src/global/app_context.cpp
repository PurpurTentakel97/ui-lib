//
// Purpur Tentakel
// 01.04.25
//

#include <uil/global/app_context.hpp>

namespace uil::global {
    void AppContext::reset() {
        m_input.reset();
    }

    AppContext& AppContext::instance() {
        static AppContext app_context{};
        return app_context;
    }

    InputManager& AppContext::input() {
        return m_input;
    }
    InputManager const& AppContext::input() const {
        return m_input;
    }
} // namespace uil::global
