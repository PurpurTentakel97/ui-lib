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

    SceneManager::ScenePtr_Weak SceneManager::push_back(ScenePtr to_push) {
        return insert_element(0, std::move(to_push));
    }

    SceneManager::ScenePtr_Weak SceneManager::push_front(ScenePtr to_push) {
        return insert_element(m_scenes.end() - m_scenes.begin(), std::move(to_push));
    }

    SceneManager::ScenePtr_Weak SceneManager::push_at(cpt::usize const index, ScenePtr to_push) {
        if (index > m_scenes.size()) {
            throw BadSceneIndex("index is out of bounce");
        }

        if (index == m_scenes.size()) {
            return push_front(std::move(to_push));
        }

        return insert_element(index, std::move(to_push));
    }

    SceneManager::ScenePtr_Weak SceneManager::push_after(ScenePtr_Weak const& scene, ScenePtr to_push) {
        if (auto const shared_before = scene.lock(); shared_before) {
            auto const iterrator
                    = std::find_if(m_scenes.begin(), m_scenes.end(), [&b = shared_before](auto const& elem) {
                          return b.get() == elem.get();
                      });
            if (iterrator == m_scenes.end()) {
                throw BadScenePointer("not able to find before element in scenes vector");
            }
            return insert_element(iterrator - m_scenes.begin(), std::move(to_push));
        }

        throw BadScenePointer("weak_ptr was ecpired");
    }

    SceneManager::ScenePtr_Weak SceneManager::push_before(ScenePtr_Weak const& scene, ScenePtr to_push) {
        if (auto const shared_after = scene.lock(); shared_after) {
            auto const iteraor = std::find_if(m_scenes.begin(), m_scenes.end(), [&a = shared_after](auto const& elem) {
                return a.get() == elem.get();
            });
            if (iteraor == m_scenes.end()) {
                throw BadScenePointer("not able to find after element in scenes vector");
            }

            return insert_element(iteraor - m_scenes.begin() + 1, std::move(to_push));
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    SceneManager::ScenePtr SceneManager::pop_back() {
        if (m_scenes.empty()) {
            throw BadSceneErase("empty scenes vector");
        }

        auto temp = m_scenes.front();
        m_scenes.erase(m_scenes.begin());
        return std::move(temp);
    }

    SceneManager::ScenePtr SceneManager::pop_front() {
        if (m_scenes.empty()) {
            throw BadSceneErase("empty scenes vector");
        }

        auto temp = m_scenes.back();
        m_scenes.pop_back();
        return std::move(temp);
    }

    SceneManager::ScenePtr SceneManager::pop_at(cpt::usize const index) {
        if (index >= m_scenes.size()) {
            throw BadSceneIndex("index out of range while pop at");
        }

        auto temp = m_scenes.at(index);
        erase(index);
        return std::move(temp);
    }

    SceneManager::ScenePtr SceneManager::pop_after(ScenePtr_Weak const& scene) {
        if (auto const shared_before = scene.lock(); shared_before) {
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
            auto temp = std::move(*(iterator - 1));
            erase(iterator - m_scenes.begin() - 1);
            return std::move(temp);
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    SceneManager::ScenePtr SceneManager::pop_before(ScenePtr_Weak const& scene) {
        if (auto const shared_after = scene.lock(); shared_after) {
            auto const iterator = std::find_if(m_scenes.begin(), m_scenes.end(), [&a = shared_after](auto const& elem) {
                return a.get() == elem.get();
            });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find element before in the scenes vector");
            }
            if (iterator == m_scenes.end() - 1) {
                throw BadSceneErase("No element after the provided element");
            }
            auto temp = std::move(*(iterator + 1));
            erase(iterator - m_scenes.begin() + 1);
            return std::move(temp);
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    SceneManager::ScenePtr SceneManager::pop_this(ScenePtr_Weak const& to_pop) {
        if (auto const shared_to_pop = to_pop.lock(); shared_to_pop) {
            auto const iterator
                    = std::find_if(m_scenes.begin(), m_scenes.end(), [&d = shared_to_pop](auto const elem) {
                          return d.get() == elem.get();
                      });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find element in the scenes vector");
            }
            auto temp = std::move(*iterator);
            erase(iterator - m_scenes.begin());
            return std::move(temp);
        }

        throw BadScenePointer("weak_ptr was expired");
    }

    void SceneManager::erase_back() {
        if (m_scenes.empty()) {
            throw BadSceneErase("empty scenes vector");
        }
        m_scenes.erase(m_scenes.begin());
    }

    void SceneManager::erase_front() {
        if (m_scenes.empty()) {
            throw BadSceneErase("empty scenes vector");
        }
        m_scenes.pop_back();
    }

    void SceneManager::erase_at(cpt::usize const index) {
        if (index >= m_scenes.size()) {
            throw BadSceneIndex("index out of range while erasing a scene");
        }

        erase(index);
    }

    void SceneManager::erase_after(ScenePtr_Weak const& scene) {
        if (auto const shared_before = scene.lock(); shared_before) {
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

    void SceneManager::erase_before(ScenePtr_Weak const& scene) {
        if (auto const shared_after = scene.lock(); shared_after) {
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
            auto const iterator
                    = std::find_if(m_scenes.begin(), m_scenes.end(), [&d = shared_to_delete](auto const elem) {
                          return d.get() == elem.get();
                      });
            if (iterator == m_scenes.end()) {
                throw BadScenePointer("not able to find element in the scenes vector");
            }
            erase(iterator - m_scenes.begin());
            return;
        }

        throw BadScenePointer("weak_ptr was expired");
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
