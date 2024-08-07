//
// Purpur Tentakel
// 07.08.24
//

#pragma once

namespace uil {
    class BaseElement {
    private:
        bool m_active = true;

    public:
        [[nodiscard]] bool active() const;
        void set_active(bool active);
    };
} // namespace uil
