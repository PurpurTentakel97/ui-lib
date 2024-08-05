//
// Purpur Tentakel
// 06.07.24
//

#include <ranges>
#include <uil/context.hpp>
#include <uil/scene_manager.hpp>

namespace uil {
    SceneManager::ScenePtr_Weak SceneManager::insert_element(cpt::usize const offset, ScenePtr scene) {
        ScenePtr_Weak ptr = scene;
        m_scenes.insert(m_scenes.begin() + static_cast<cpt::i64>(offset), std::move(scene));
        return ptr;
    }

    void SceneManager::erase(cpt::usize const offset) {
        m_scenes.erase(m_scenes.begin() + static_cast<cpt::i64>(offset));
    }

    SceneManager::SceneManager(cpt::Vec2_i const resolution) : m_resolution{ resolution } { }

    SceneManager::ScenePtr_Weak SceneManager::push_back(ScenePtr scene) {
        return insert_element(0, std::move(scene));
    }

    SceneManager::ScenePtr_Weak SceneManager::push_front(ScenePtr scene) {
        return insert_element(m_scenes.end() - m_scenes.begin(), std::move(scene));
    }

    SceneManager::ScenePtr_Weak SceneManager::push_at(cpt::usize const index, ScenePtr scene) {
        if (index > m_scenes.size()) {
            throw BadSceneIndex("index is out of bounce");
        }

        if (index == m_scenes.size()) {
            return push_front(std::move(scene));
        }

        return insert_element(index, std::move(scene));
    }

    SceneManager::ScenePtr_Weak SceneManager::push_after(ScenePtr_Weak const& before, ScenePtr scene) {
        if (auto const shared_before = before.lock(); shared_before) {
            auto const iterrator
                    = std::find_if(m_scenes.begin(), m_scenes.end(), [&b = shared_before](auto const& elem) {
                          return b.get() == elem.get();
                      });
            if (iterrator == m_scenes.end()) {
                throw BadScenePointer("not able to find before element in scenes vector");
            }
            return insert_element(iterrator - m_scenes.begin(), std::move(scene));
        }

        throw BadScenePointer("weak_ptr was ecpired");
    }

    SceneManager::ScenePtr_Weak SceneManager::push_before(ScenePtr_Weak const& after, ScenePtr scene) {
        if (auto const shared_after = after.lock(); shared_after) {
            auto const iteraor = std::find_if(m_scenes.begin(), m_scenes.end(), [&a = shared_after](auto const& elem) {
                return a.get() == elem.get();
            });
            if (iteraor == m_scenes.end()) {
                throw BadScenePointer("not able to find after element in scenes vector");
            }

            return insert_element(iteraor - m_scenes.begin() + 1, std::move(scene));
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    void SceneManager::erase_back() {
        m_scenes.erase(m_scenes.begin());
    }

    void SceneManager::erase_front() {
        m_scenes.pop_back();
    }

    void SceneManager::erase_at(cpt::usize const index) {
        if (index >= m_scenes.size()) {
            throw BadSceneIndex("index out of range while erasing a scene");
        }

        erase(index);
    }

    void SceneManager::erase_after(ScenePtr_Weak const& before) {
        if (auto const shared_before = before.lock(); shared_before) {
            auto const iterator
                    = std::find_if(m_scenes.begin(), m_scenes.end(), [&b = shared_before](auto const& elem) {
                          return b.get() == elem.get();
                      });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find element before in the scenes vector");
            }
            if (iterator == m_scenes.begin()) {
                throw BadSceneErase("No element before the provided element");
            }
            erase(iterator - m_scenes.begin() - 1);
            return;
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    void SceneManager::erase_before(ScenePtr_Weak const& after) {
        if (auto const shared_after = after.lock(); shared_after) {
            auto const iterator = std::find_if(m_scenes.begin(), m_scenes.end(), [&a = shared_after](auto const& elem) {
                return a.get() == elem.get();
            });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find element before in the scenes vector");
            }
            if (iterator == m_scenes.end() - 1) {
                throw BadSceneErase("No element after the provided element");
            }
            erase(iterator - m_scenes.begin() + 1);
            return;
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    void SceneManager::erase_this(ScenePtr_Weak const& to_delete) {
        if (auto const shared_to_delete = to_delete.lock(); shared_to_delete) {
            erase_this(shared_to_delete.get());
            return;
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    void SceneManager::erase_this(Scene const* to_delete) {
        auto const iterator = std::find_if(
                m_scenes.begin(), m_scenes.end(), [&d = to_delete](auto const elem) { return d == elem.get(); });
        if (iterator == m_scenes.end()) {
            throw BadScenePointer("not able to find element in the scenes vector");
        }
        erase(iterator - m_scenes.begin());
    }

    bool SceneManager::handle_input(Context const& context) const {
        return std::ranges::all_of(std::ranges::views::reverse(m_scenes),
                                   [&c = context](auto const& s) { return s->handle_input(c); });
    }

    bool SceneManager::update(Context const& context) const {
        return std::ranges::all_of(std::ranges::views::reverse(m_scenes),
                                   [&c = context](auto const& s) { return s->update(c); });
    }

    void SceneManager::render(Context const& context) const {
        for (auto const& s : m_scenes) {
            s->render(context);
        }
    }

    void SceneManager::resize(Context const& context) {
        m_resolution = context.resolution;
        for (auto const& s : m_scenes) {
            s->resize(context);
        }
    }
} // namespace uil
