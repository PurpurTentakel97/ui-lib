//
// Purpur Tentakel
// 19.05.24
//

#pragma once

#include <stdexcept>

namespace uil {
    /**
     * use for any kind of error inside the uil::Callback class.
     */
    class CallbackException final : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    /**
     * use if a division would need to devide by zero.
     */
    class DivideByZero final : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    /**
     * use if a unexpected resolution ocures at certain operation.
     * this mostly occures when the resolution enum does not have a predefined value.
     */
    class BadResolution final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * use if an unexpected alignment ocures at certain operation.
     * this mostly occures when the alignment enum does not have a predefined value.
     */
    class BadAlignment final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * use if an unexpected movement ocures at certain operation.
     * this mostly occures when the movement enum does not have a predefined value.
     */
    class BadMovementType final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * use if an execpected index ocures in any scene operation.
     */
    class BadSceneIndex final : public std::out_of_range {
        using std::out_of_range::out_of_range;
    };

    /**
     * us if the provided scene could not be found.
     */
    class BadScenePointer final : public std::logic_error {
        using std::logic_error::logic_error;
    };
} // namespace uil
