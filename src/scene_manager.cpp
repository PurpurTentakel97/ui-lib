//
// Purpur Tentakel
// 06.07.24
//

#include <ranges>
#include <uil/update_context.hpp>
#include <uil/scene_manager.hpp>
#include <uil/global/app_context.hpp>

namespace uil {
    bool SceneManager::handle_input(UpdateContext const& context) const {
        return std::ranges::all_of(elements(),
                                   [&c = context](auto const& s) {
                                       if (s->active()) {
                                           return s->handle_input(c);
                                       }
                                       return true;
                                   });
    }

    bool SceneManager::update(UpdateContext const& context) const {
        return std::ranges::all_of(elements(),
                                   [&c = context](auto const& s) {
                                       if (s->active()) {
                                           return s->update(c);
                                       }
                                       return true;
                                   });
    }

    void SceneManager::render() const {
        for (auto const& s : std::ranges::views::reverse(elements())) {
            if (s->active()) {
                s->render();
            }
        }
    }

    void SceneManager::resize() {
        BaseManager::resize();
        for (auto const& s : elements()) {
            s->resize();
        }
    }
} // namespace uil
