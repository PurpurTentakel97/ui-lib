//
// Purpur Tentakel
// 06.07.24
//

#include <uil/context.hpp>
#include <uil/element.hpp>
#include <uil/scene.hpp>

namespace uil {
    Scene::Scene(cpt::Vec2_i const resolution) : BaseManager{ resolution } { }

    bool Scene::handle_input(Context const& context) const {
        auto keep_checking = true;
        for (auto const& e : elements()) {
            if (e->active()) {
                keep_checking &= e->handle_input(context);
            }
        }
        on_check.invoke(*this);
        return keep_checking;
    }

    bool Scene::update(Context const& context) const {
        auto keep_updating = true;
        for (auto const& e : elements()) {
            if (e->active()) {
                keep_updating &= e->update(context);
            }
        }
        on_update.invoke(*this);
        return keep_updating;
    }

    void Scene::render(Context const& context) const {
        for (auto const& e : elements()) {
            if (e->active()) {
                e->render(context);
            }
        }
        on_render.invoke(*this);
    }

    void Scene::resize(Context const& context) {
        BaseManager::resize(context);
        for (auto const& e : elements()) {
            e->resize(context);
        }
        on_resize.invoke(*this);
    }
} // namespace uil
