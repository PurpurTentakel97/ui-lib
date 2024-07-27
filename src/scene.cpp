//
// Purpur Tentakel
// 06.07.24
//

#include <uil/context.hpp>
#include <uil/element.hpp>
#include <uil/scene.hpp>

namespace uil {
    bool Scene::check(Context const& context) const {
        for (auto const& e : m_elements) {
            if (not e->check(context)) {
                return false;
            }
        }
        on_check.invoke(*this);
        return true;
    }

    bool Scene::update(Context const& context) const {
        for (auto const& e : m_elements) {
            if (not e->update(context)) {
                return false;
            }
        }
        on_update.invoke(*this);
        return true;
    }

    bool Scene::render(Context const& context) const {
        for (auto const& e : m_elements) {
            if (not e->render(context)) {
                return false;
            }
        }
        on_render.invoke(*this);
        return true;
    }

    void Scene::resize(Context const& context) const {
        for (auto const& e : m_elements) {
            e->resize(context);
        }
        on_resize.invoke(*this);
    }
} // namespace uil
