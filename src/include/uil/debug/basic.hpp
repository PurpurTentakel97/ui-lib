//
// Purpur Tentakel
// 26.05.25
//

#pragma once

namespace uil::debug {
    template<class T>
    class BasicDebug {
    protected:
#ifndef NDEBUG
        bool m_active = false;
#endif

    public:
        virtual ~BasicDebug()       = default;
        virtual void exec(T const*) const = 0;

        void set([[maybe_unused]] bool const active) {
#ifndef NDEBUG
            m_active = active;
#endif
        }

        [[nodiscard]] bool active() const {
#ifndef NDEBUG
            return m_active;
#else
            return false;
#endif
        }
    };
} // namespace uil::debug
