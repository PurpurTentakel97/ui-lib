//
// Purpur Tentakel
// 06.07.24
//

#pragma once
#include <algorithm>
#include <memory>
#include <uil/scene.hpp>
#include <vector>

namespace uil {
    struct Context;

    /**
     * manages all scene in the game.
     * checks, updates, renders and resizes all emplaced scenes.
     * stops checking and updating when a scene returns false.
     */
    class SceneManager final {
    public:
        using ScenePtr      = std::shared_ptr<Scene>;
        using ScenePtr_Weak = std::weak_ptr<Scene>;
        using SceneVector   = std::vector<ScenePtr>;

    private:
        SceneVector m_scenes{};
        cpt::Vec2_i m_resolution;

        template<std::derived_from<Scene> T, typename... Args>
        std::weak_ptr<T> emplace_emelent(cpt::usize const offset, Args&&... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            auto elem            = std::make_shared<T>(m_resolution, std::forward<Args>(args)...);
            std::weak_ptr<T> ptr = elem;
            m_scenes.insert(m_scenes.begin() + static_cast<cpt::i64>(offset), std::move(elem));
            return ptr;
        }

        ScenePtr_Weak insert_element(cpt::usize offset, ScenePtr scene);

        void erase(cpt::usize offset);

    public:
        /**
         *
         * @param resolution current resolution
         */
        explicit SceneManager(cpt::Vec2_i resolution);

        /**
         * construct the scene T with parameters Args... and emplaced it at the front of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene as a weak_ptr
         */
        template<std::derived_from<Scene> T, typename... Args>
        std::weak_ptr<T> emplace_back(Args&&... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return emplace_emelent<T>(0, args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it at the end of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene as a weak_ptr
         */
        template<std::derived_from<Scene> T, typename... Args>
        std::weak_ptr<T> emplace_front(Args&&... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return emplace_emelent<T>(m_scenes.end() - m_scenes.begin(), args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it at a certain index of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param index  provides the index the new scene is empaced to
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene as a weak_ptr
         * @throw BadSceneIndex will throw when index is out of range
         */
        template<std::derived_from<Scene> T, typename... Args>
        std::weak_ptr<T> emplace_at(cpt::usize const index, Args&&... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            if (index > m_scenes.size()) {
                throw BadSceneIndex("index is out of bounce");
            }
            if (index == m_scenes.size()) {
                return emplace_front<T>(args...);
            }

            return emplace_emelent<T>(index, args...);
        }

        /**
         * construct the scene T with parameters Args... and emplaced it before a provided scene of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param scene proviedes the scene pointer the new scene gets emplaced before
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene as a weak_ptr
         * @throw BadScenePointer throws when provided before scene can not be fount in the scenes vector
         * @throw BadScenePointer throws when provided before scene is expired
         */
        template<std::derived_from<Scene> T, typename... Args>
        std::weak_ptr<T> emplace_after(std::weak_ptr<T> const& scene, Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            if (auto const shared_scene = scene.lock(); shared_scene) {
                auto const iterator
                        = std::find_if(m_scenes.begin(), m_scenes.end(), [&b = shared_scene](auto const& elem) {
                              return elem.get() == b.get();
                          });
                if (iterator == m_scenes.end()) {
                    throw BadScenePointer("not able to find before element in scenes vector");
                }

                return emplace_emelent<T>(iterator - m_scenes.begin(), args...);
            }

            throw BadScenePointer("weak_ptr was expired");
        }

        /**
         * construct the scene T with parameters Args... and emplaced it after a provided scene of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T scene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param scene proviedes the scene pointer the new scene gets emplaced after
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene as a weak_ptr
         * @throw BadScenePointer throws when provided after scene can not be found in the scenes vector
         * @throw BadScenePointer throws when provided after scene is expired
         */
        template<std::derived_from<Scene> T, typename... Args>
        std::weak_ptr<T> emplace_before(std::weak_ptr<T> const& scene, Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            if (auto const shared_scene = scene.lock(); shared_scene) {
                auto const iterator
                        = std::find_if(m_scenes.begin(), m_scenes.end(), [&a = shared_scene](auto const& elem) {
                              return elem.get() == a.get();
                          });
                if (iterator == m_scenes.end()) {
                    throw BadScenePointer("not able to find after element in scenes vector");
                }

                return emplace_emelent<T>(iterator - m_scenes.begin() + 1, args...);
            }

            throw BadScenePointer("weak_ptr was expired");
        }

        /**
         * pushed the scene at the front of the scene vector.
         * all pushed scenes will be checked, updated, rendered and resized.
         *
         * @param to_push the scene that gets pushed into the vector
         * @return pointer of the pushed scene as a weak_ptr
         */
        ScenePtr_Weak push_back(ScenePtr to_push);

        /**
         * pushed the scene at the end of the scene vector.
         * all pushed scenes will be checked, updated, rendered and resized.
         *
         * @param to_push the scene that gets pushed into the vector
         * @return pointer of the pushed scene as a weak_ptr
         */
        ScenePtr_Weak push_front(ScenePtr to_push);

        /**
         * pushes the scene at a certain index of the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * @param index provides the index the new scene is pushed to
         * @param to_push the scene that gets pushed into the vector
         * @return pointer of the pushed scene as a weak_ptr
         * @throw BadSceneIndex will throw when index is out of range
         */
        ScenePtr_Weak push_at(cpt::usize index, ScenePtr to_push);

        /**
         * pushes the scene before a provided scene of the scene vector.
         * all pushed scenes will be checked, updated, rendered and resized.
         *
         * @param scene proviedes a scene pointer that holds the scene befor the pushed scene
         * @param to_push the scene that gets pushed
         * @return pointer of the pushed scene as a weak_ptr
         * @throw BadScenePointer throws when provided before scene can not be fount in the scenes vector
         * @throw BadScenePointer throws when provided before scene is expired
         */
        ScenePtr_Weak push_after(ScenePtr_Weak scene, ScenePtr to_push);

        /**
         * pushes the scene after a provided scene of the scene vector.
         * all pushed scenes will be checked, updated, rendered and resized.
         *
         * @param scene proviedes a scene pointer that holds the scene after the pushed scene
         * @param to_push the scene that gets pushed
         * @return pointer of the pushed scene as a weak_ptr
         * @throw BadScenePointer throws when provided before scene can not be fount in the scenes vector
         * @throw BadScenePointer throws when provided before scene is expired
         */
        ScenePtr_Weak push_before(ScenePtr_Weak scene, ScenePtr to_push);

        /**
         * pops the first element of the vector.
         * that is the most bottom rendered element.
         *
         * @return shared_ptr of the poped scene
         * @throw BadSceneErase throws when scenes vector is empty
         */
        ScenePtr pop_back();

        /**
         * pops the last element of the vector.
         * that is the most front rendered element.
         *
         * @return shared_ptr of the poped scene
         * @throw BadSceneErase throws when scenes vector is empty
         */
        ScenePtr pop_front();

        /**
         * pops a specific index in the scene vector.
         * notice that index 0 is the most bottom rendered element.
         *
         * @param index rovides the index that will be poped
         * @return shared_ptr of the poped scene
         * @throw BadSceneIndex will throw when index is out of range
         */
        ScenePtr pop_at(cpt::usize index);

        /**
         * pops a scene that is located one before the provided scene in the scenes vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param scene the element before the element that will be poped
         * @return shared_ptr of the poped scene
         * @throw BadScenePointer throws when provided before scene can not be found in the scenes vector
         * @throw BadScenePointer throws when provided before scene is expired
         * @throw BadSceneErase throws when provided before scene is the first element in the scenes vector
         */
        ScenePtr pop_after(ScenePtr_Weak scene);

        /**
         * pops a scene that is located one after the provided scene in the scenes vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param scene the element after the element that wiill be deleted
         * @return shared_ptr of the poped scene
         * @throw BadScenePointer throws when provided after scene can not be found in the scenes vector
         * @throw BadScenePointer throws when provided after scene is expired
         * @throw BadSceneErase throws when provided after scene is the last element in the scenes vector
         */
        ScenePtr pop_before(ScenePtr_Weak scene);

        /**
         * pops the provided scene.
         * if there are no more shared_ptr the scene will get deleted.
         *
         * @param to_pop scene that gets poped
         * @return shared_ptr of the poped scene
         * @throw BadScenePointer throws when provided scene can not be found in the scenes vector
         */
        ScenePtr pop_this(ScenePtr_Weak to_pop);

        /**
         * erases the first element of the vector.
         * that is the most bottom rendered element.
         *
         * @throw BadSceneErase thows when scenes vector is empty
         */
        void erase_back();
        /**
         * erases the last element of the vector.
         * that is the most front rendered element.
         *
         * @throw BadSceneErase thows when scenes vector is empty
         */
        void erase_front();

        /**
         * erases a specific index in the scene vector.
         * notice that index 0 is the most bottom rendered element.
         *
         * @param index provides the index that will be erased
         * @throw BadSceneIndex will throw when index is out of range
         */
        void erase_at(cpt::usize index);
        /**
         * erases a scene that is located one before the provided scene in the scenes vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param scene the element before the element that will be deleted
         * @throw BadScenePointer throws when provided before scene can not be found in the scenes vector
         * @throw BadScenePointer throws when provided before scene is expired
         * @throw BadSceneErase throws when provided before scene is the first element in the scenes vector
         */
        void erase_after(ScenePtr_Weak scene);

        /**
         * erases a scene that is located one after the provided scene in the scenes vector.
         * that is the element that gets rendered behind the provided one.
         *
         * @param scene the element after the element that wiill be deleted
         * @throw BadScenePointer throws when provided after scene can not be found in the scenes vector
         * @throw BadScenePointer throws when provided after scene is expired
         * @throw BadSceneErase throws when provided after scene is the last element in the scenes vector
         */
        void erase_before(ScenePtr_Weak scene);

        /**
         * erases the provided scene.
         * if there are no more shared_ptr the scene will get deleted.
         *
         * @param to_delete scene that gets deleted
         * @throw BadScenePointer throws when provided scene can not be found in the scenes vector
         */
        void erase_this(ScenePtr_Weak to_delete);

        /**
         * calls all emplaced scene from top to bottom to check.
         * stops checking when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep checking
         */
        [[nodiscard]] bool handle_input(Context const& context) const;
        /**
         * calls all emplaced scene from top to bottom to update.
         * stops updating when a scene has returned false.
         *
         * @param context all changes of the last frame
         * @return whether the next system should keep updting
         */
        [[nodiscard]] bool update(Context const& context) const;
        /**
         * calls all emplaced scene from bottom to top to render.
         *
         * @param context all changes of the last frame
         */
        void render(Context const& context) const;
        /**
         * calls all emplaced scene to resize.
         *
         * @param context all changes of the last frame
         */
        void resize(Context const& context);
    };
} // namespace uil
