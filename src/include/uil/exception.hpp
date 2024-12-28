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
     * use if a division would need to divide by zero.
     */
    class DivideByZero final : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    /**
     * use if an unexpected resolution occur at certain operation.
     * this mostly occur when the resolution enum does not have a predefined value.
     */
    class BadResolution final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * use if an unexpected alignment occur at certain operation.
     * this mostly occur when the alignment enum does not have a predefined value.
     */
    class BadAlignment final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * use if an unexpected movement occur at certain operation.
     * this mostly occur when the movement enum does not have a predefined value.
     */
    class BadMovementType final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * use if an unexpected index occur in any scene operation.
     */
    class BadElementIndex final : public std::out_of_range {
        using std::out_of_range::out_of_range;
    };

    /**
     * us if the provided scene could not be found.
     */
    class BadElementPointer final : public std::logic_error {
        using std::logic_error::logic_error;
    };

    /**
     * Thrown when attempting to erase an element in a scenario
     * where such an operation is invalid or not possible.
     */
    class BadElementErase final : public std::logic_error {
        using std::logic_error::logic_error;
    };
} // namespace uil
