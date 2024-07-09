//
// Purpur Tentakel
// 06.07.24
//

#include <uil/scene_manager.hpp>

namespace uil {
    void SceneManager::add_scene(std::unique_ptr<Scene> scene) {
        m_scenes.push_back(std::move(scene));
    }

    bool SceneManager::check(Vector2 const& mousePosition) const {
        for (auto const& s : m_scenes) {
            if (not s->check(mousePosition)) {
                return false;
            }
        }
        return true;
    }

    bool SceneManager::update() const {
        for (auto const& s : m_scenes) {
            if (not s->update()) {
                return false;
            }
        }
        return true;
    }

    bool SceneManager::render(Font const* const font) const {
        for (auto const& s : m_scenes) {
            if (not s->render(font)) {
                return false;
            }
        }
        return true;
    }

    void SceneManager::resize(cpt::Vec2_i const& resolution) const {
        for (auto const& s : m_scenes) {
            s->resize(resolution);
        }
    }
} // namespace uil
