//
// Purpur Tentakel
// 06.07.24
//

#include <uil/update_context.hpp>
#include <uil/element.hpp>
#include <uil/scene.hpp>

namespace uil {
    bool Scene::handle_input(UpdateContext const& context) const {
        auto keep_checking = true;
        for (auto const& e : elements()) {
            if (e->active()) {
                keep_checking &= e->handle_input(context);
            }
        }
        on_check.invoke(*this);
        return keep_checking;
    }

    bool Scene::update(UpdateContext const& context) const {
        auto keep_updating = true;
        for (auto const& e : elements()) {
            if (e->active()) {
                keep_updating &= e->update(context);
            }
        }
        on_update.invoke(*this);
        return keep_updating;
    }

    void Scene::render() const {
        for (auto const& e : elements()) {
            if (e->active()) {
                e->render();
            }
        }
        on_render.invoke(*this);
    }

    void Scene::resize() {
        for (auto const& e : elements()) {
            e->resize();
        }
        on_resize.invoke(*this);
    }
} // namespace uil
