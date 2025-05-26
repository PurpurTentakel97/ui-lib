//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <uil/base_element.hpp>
#include <uil/base_manager.hpp>
#include <uil/element.hpp>

namespace uil {
    struct UpdateContext;

    /**
     * base class for all scenes in this library.
     * it contains all elements within a scene.
     * the scene checks, updates, renders and resizes all elements.
     */
    class Scene : public BaseManager<UIElement>, public BaseElement {
    public:
        Callback<Scene const&> on_check{};  ///< contains Scene
        Callback<Scene const&> on_update{}; ///< contains Scene
        Callback<Scene const&> on_render{}; ///< contains Scene
        Callback<Scene const&> on_resize{}; ///< contains Scene

        /**
         * this constructor can do exactly nothing.
         * I need it to be able to add the resolution in the scene_manager.
         */
        using BaseManager::BaseManager;
        Scene(Scene const&)            = delete; ///< deleted because it will be used in unique_ptr
        Scene(Scene&&)                 = delete; ///< deleted because it will be used in unique_ptr
        Scene& operator=(Scene const&) = delete; ///< deleted because it will be used in unique_ptr
        Scene& operator=(Scene&&)      = delete; ///< deleted because it will be used in unique_ptr

        /**
         * checking all elements in the scene. provides the context.
         * override this when the derived scene has to check additional stuff.
         * make sure to call Scene::check() and use the return bool.
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep checking
         */
        [[nodiscard]] virtual bool handle_input(UpdateContext const& context) const;
        /**
         * updating all elements in the scene. provides the context.
         *
         * override this when the derived scene has to update additional stuff.
         * make sure to call Scene::update() and use the return bool.
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep updating
         */
        [[nodiscard]] virtual bool update(UpdateContext const& context) const;
        /**
         * rendering all elements in the scene. provides the context.
         *
         * override this when the derived scene has to render additional stuff.
         * make sure to call Scene::render().
         */
        virtual void render() const;
        /**
         * resizing all elements in the scene. provides the context.
         *
         * override this when the derived scene has to resize additional stuff.
         * make sure to call Scene::resize().
         */
        void resize() override;
    };
}; // namespace uil
