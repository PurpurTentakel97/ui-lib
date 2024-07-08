//
// Purpur Tentakel
// 06.07.24
//

#include <uil/scene.hpp>
#include <uil/ui_element.hpp>

namespace uil {
    bool Scene::render(Font const* const font) const {
        for (auto const& e : m_elements) {
            if (not e->render(font)) {
                return false;
            }
        }
        return true;
    }
} // namespace uil
