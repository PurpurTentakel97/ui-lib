//
// Purpur Tentakel
// 06.07.24
//

#include <uil/context.hpp>
#include <uil/element.hpp>
#include <uil/scene.hpp>

namespace uil {
    Scene::Scene(cpt::Vec2_i) { }

    bool Scene::check(Context const& context) const {
        auto keep_checking = true;
        for (auto const& e : m_elements) {
            keep_checking &= e->check(context);
        }
        on_check.invoke(*this);
        return keep_checking;
    }

    bool Scene::update(Context const& context) const {
        auto keep_updating = true;
        for (auto const& e : m_elements) {
            keep_updating &= e->update(context);
        }
        on_update.invoke(*this);
        return keep_updating;
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
