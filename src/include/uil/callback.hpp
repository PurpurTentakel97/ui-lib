//
// Purpur Tentakel
// 17.05.24
//

#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cpt/types.hpp>
#include <functional>
#include <uil/exception.hpp>
#include <vector>

namespace uil {
    template<typename... C>
    class Callback final {
    private:
        using function_ty = std::function<void(C...)>;
        std::vector<function_ty> m_callbacks;

    public:
        void invoke(C... arguments) const {
            for (auto const& c : m_callbacks) {
                assert(c);
                c(arguments...);
            }
        }

        void clear() {
            m_callbacks.clear();
        }

        [[nodiscard]] cpt::usize size() const {
            return m_callbacks.size();
        }

        [[nodiscard]] bool is_empty() const {
            return m_callbacks.empty();
        }

        Callback& operator+=(std::convertible_to<function_ty> auto&& func) {
            auto function = function_ty{ std::forward<decltype(func)>(func) };
            if (not function) {
                throw CallbackException("register of bad callback function");
            }
            m_callbacks.emplace_back(std::move(function));
            return *this;
        }
    };
} // namespace uil
