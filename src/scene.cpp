//
// Purpur Tentakel
// 06.07.24
//

#include <uil/scene.hpp>
#include <uil/ui_element.hpp>

namespace uil {
    bool Scene::check(Vector2 const& mousePosition) const {
        for (auto const& e : m_elements) {
            if (not e->check(mousePosition)) {
                return false;
            }
        }
        on_check.invoke(*this);
        return true;
    }

    bool Scene::update() const {
        for (auto const& e : m_elements) {
            if (not e->update()) {
                return false;
            }
        }
        on_update.invoke(*this);
        return true;
    }

    bool Scene::render(Font const* const font) const {
        for (auto const& e : m_elements) {
            if (not e->render(font)) {
                return false;
            }
        }
        on_render.invoke(*this);
        return true;
    }

    void Scene::resize(cpt::Vec2_i const& resolution) const {
        for (auto const& e : m_elements) {
            e->resize(resolution);
        }
        on_resize.invoke(*this);
    }
} // namespace uil
