//
// Purpur Tentakel
// 06.07.24
//

#include <algorithm>
#include <uil/scene.hpp>
#include <uil/ui_element.hpp>

namespace uil {
    void Scene::add_element(std::unique_ptr<UIElement> element) {
        m_elements.push_back(std::move(element));
    }

    bool Scene::render() const {
        for (auto const& e : m_elements) {
            if (not e->render()) {
                return false;
            }
        }
        return true;
    }
} // namespace uil
