//
// Purpur Tentakel
// 01.04.25
//

#include <algorithm>
#include <functional>
#include <uil/global/input.hpp>

namespace uil::global {
    cpt::usize InputManager::next_id() {
        return m_id_counter++;
    }
} // namespace uil::global
