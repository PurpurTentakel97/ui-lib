//
// Purpur Tentakel
// 15.03.25
//

#pragma once

namespace uil::debug {
    template<class T>
    class Debug {
    protected:
#ifndef NDEBUG
        bool m_value = false;
#endif

    public:
        virtual ~Debug() = default;

        virtual void exec(T const*) const = 0;

        void set([[maybe_unused]] bool const value) {
#ifndef NDEBUG
            m_value = value;
#endif
        }

        [[nodiscard]] bool get() const {
#ifndef NDEBUG
            return m_value;
#else
            return false;
#endif
        }
    };
} // namespace uil::debug
