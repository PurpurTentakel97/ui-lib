//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <stdexcept>

namespace uil {
    class CallbackException final : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class DivideByZero final : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class BadResolution final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    class BadAlignment final : public std::logic_error {
        using std::logic_error::logic_error;
    };
} // namespace uil
