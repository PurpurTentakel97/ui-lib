//
// Purpur Tentakel
// 24.05.24
//

#pragma once

namespace uil {
    class UpdateRenderHelper {
    protected:
        bool m_keep_handle   = true;
        bool m_keep_updating = true;

    public:
        void set_keep_handle(bool keep_handle);
        [[nodiscard]] bool keep_handle() const;

        void set_keep_updating(bool keep_updating);
        [[nodiscard]] bool keep_updating() const;
    };
} // namespace uil
