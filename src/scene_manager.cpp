//
// Purpur Tentakel
// 06.07.24
//

#include <uil/scene_manager.hpp>
#include <uil/context.hpp>

namespace uil {
    void SceneManager::add_scene(std::unique_ptr<Scene> scene) {
        m_scenes.push_back(std::move(scene));
    }

    bool SceneManager::check(Context const& context) const {
        for (auto const& s : m_scenes) {
            if (not s->check(context)) {
                return false;
            }
        }
        return true;
    }

    bool SceneManager::update(Context const& context) const {
        for (auto const& s : m_scenes) {
            if (not s->update(context)) {
                return false;
            }
        }
        return true;
    }

    bool SceneManager::render(Context const& context) const {
        for (auto const& s : m_scenes) {
            if (not s->render(context)) {
                return false;
            }
        }
        return true;
    }

    void SceneManager::resize(Context const& context) const {
        for (auto const& s : m_scenes) {
            s->resize(context);
        }
    }
} // namespace uil
