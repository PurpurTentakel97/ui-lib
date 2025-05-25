//
// Purpur Tentakel
// 06.07.24
//

#include <ranges>
#include <uil/context.hpp>
#include <uil/scene_manager.hpp>
#include <uil/global/app_context.hpp>

namespace uil {

    SceneManager::SceneManager() : BaseManager{ { 800, 600 } } {}

    bool SceneManager::handle_input(Context const& context) const {
        return std::ranges::all_of(elements(),
                                   [&c = context](auto const& s) {
                                       if (s->active()) {
                                           return s->handle_input(c);
                                       }
                                       return true;
                                   });
    }

    bool SceneManager::update(Context const& context) const {
        return std::ranges::all_of(elements(),
                                   [&c = context](auto const& s) {
                                       if (s->active()) {
                                           return s->update(c);
                                       }
                                       return true;
                                   });
    }

    void SceneManager::render(Context const& context) const {
        for (auto const& s : std::ranges::views::reverse(elements())) {
            if (s->active()) {
                s->render(context);
            }
        }
    }

    void SceneManager::resize(Context const& context) {
        BaseManager::resize(context);
        for (auto const& s : elements()) {
            s->resize(context);
        }
    }
} // namespace uil
