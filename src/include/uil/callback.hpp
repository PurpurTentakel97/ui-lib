//
// Purpur Tentakel
// 17.05.24
//

#pragma once

#include <algorithm>
#include <cassert>
#include <cpt/types.hpp>
#include <functional>
#include <uil/exception.hpp>
#include <vector>

namespace uil {
    /**
     * provides a callback. subscribe with operator+= and invoke with member function.
     *
     * @tparam C types that gets provided py the callback when it gets invoked
     */
    template<typename... C>
    class Callback final {
    private:
        using function = std::function<void(C...)>;
        std::vector<function> m_callbacks;

    public:
        /**
         * calls all callbacks that are subscript via operator+=.
         *
         * @param arguments arguments that gets provided py the callback
         */
        void invoke(C... arguments) const {
            for (auto const& c : m_callbacks) {
                assert(c);
                c(arguments...);
            }
        }

        /**
         * deletes all current callbacks.
         */
        void clear() {
            m_callbacks.clear();
        }

        /**
         *
         * @return current number of callbacks.
         */
        [[nodiscard]] cpt::usize size() const {
            return m_callbacks.size();
        }

        /**
         *
         * @return whether the callback is empty
         */
        [[nodiscard]] bool is_empty() const {
            return m_callbacks.empty();
        }

        /**
         * stores the provided callback and calls it when invoke is called.
         *
         * @param func function for callback
         * @return callback instance
         * @throw uil::CallbackException when it's not possible to convert the input into the function type
         */
        Callback& operator+=(std::convertible_to<function> auto&& func) {
            auto f = function{ std::forward<decltype(func)>(func) };
            if (not f) {
                throw CallbackException("register of bad callback function");
            }
            m_callbacks.emplace_back(std::move(f));
            return *this;
        }
    };
} // namespace uil
