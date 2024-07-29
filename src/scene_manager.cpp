//
// Purpur Tentakel
// 06.07.24
//

#include <ranges>
#include <uil/context.hpp>
#include <uil/scene_manager.hpp>

namespace uil {
    bool SceneManager::check(Context const& context) const {
        for (auto const& s : std::ranges::views::reverse(m_scenes)) {
            if (not s->check(context)) {
                return false;
            }
        }
        return true;
    }

    bool SceneManager::update(Context const& context) const {
        for (auto const& s : std::ranges::views::reverse(m_scenes)) {
            if (not s->update(context)) {
                return false;
            }
        }
        return true;
    }

    void SceneManager::render(Context const& context) const {
        for (auto const& s : m_scenes) {
            s->render(context);
        }
    }

    void SceneManager::resize(Context const& context) const {
        for (auto const& s : m_scenes) {
            s->resize(context);
        }
    }
} // namespace uil
