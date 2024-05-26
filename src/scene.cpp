//
// Purpur Tentakel
// 24.05.24
//

#include <ranges>
#include <uil/scene.hpp>

namespace uil {
    bool Scene::handle_event(InputEvent const& event) {
        for (auto& element : std::ranges::views::reverse(m_elements)) {
            auto const stop_handle = element.handle_event(event);
            if (stop_handle) {
                return false;
            }
        }
        return m_keep_handle;
    }

    bool Scene::update() {
        for (auto& element : std::ranges::views::reverse(m_elements)) {
            auto const stop_updating = element.update();
            if (stop_updating) {
                return false;
            }
        }
        return m_keep_updating;
    }

    void Scene::resize(cpt::Vec2_i resolution) {
        for (auto& element : m_elements) {
            element.resize(resolution);
        }
    }

    void Scene::render() {
        for (auto& element : m_elements) {
            element.render();
        }
    }
} // namespace uil
