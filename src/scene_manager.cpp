//
// Purpur Tentakel
// 14.05.24
//

#include <ranges>
#include <uil/scene_manager.hpp>

namespace uil {
    bool SceneManager::handle_event(InputEvent const& event) {
        for (auto& scene : std::ranges::views::reverse(m_scenes)) {
            auto const handled = scene.handle_event(event);
            if (handled) {
                return false;
            }
        }
        return true;
    }

    bool SceneManager::update() {
        for (auto& scene : std::ranges::views::reverse(m_scenes)) {
            auto const stop_updating = scene.update();
            if (stop_updating) {
                return false;
            }
        }
        return true;
    }

    void SceneManager::resize(cpt::Vec2i const resolution) {
        for (auto& scene : m_scenes) {
            scene.resize(resolution);
        }
    }

    void SceneManager::render() {
        for (auto& scene : m_scenes) {
            scene.render();
        }
    }
} // namespace uil
