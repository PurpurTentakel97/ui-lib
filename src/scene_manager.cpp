//
// Purpur Tentakel
// 06.07.24
//

#include <uil/scene_manager.hpp>

namespace uil {
    void SceneManager::add_scene(std::unique_ptr<Scene> scene) {
        m_scenes.push_back(std::move(scene));
    }

    bool SceneManager::render() const {
        for (auto const& s : m_scenes) {
            if (not s->render()) {
                return false;
            }
        }
        return true;
    }
} // namespace uil
