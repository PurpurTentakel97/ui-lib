//
// Purpur Tentakel
// 24.05.24
//

#include <uil/update_render_helper.hpp>

namespace uil {
    void UpdateRenderHelper::set_keep_handle(bool const keep_handle) {
        m_keep_handle = keep_handle;
    }

    bool UpdateRenderHelper::keep_handle() const {
        return m_keep_handle;
    }

    void UpdateRenderHelper::set_keep_updating(bool const keep_updating) {
        m_keep_updating = keep_updating;
    }

    bool UpdateRenderHelper::keep_updating() const {
        return m_keep_updating;
    }
} // namespace uil
