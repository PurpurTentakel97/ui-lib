//
// Purpur Tentakel
// 06.07.24
//

#pragma once

#include <memory>
#include <uil/element.hpp>
#include <vector>

namespace uil {
    struct Context;

    /**
     * base class for all scenes in this library.
     * it contains all elements within a scene.
     * the scene checks, updates, renders and resizes all elements.
     */
    class Scene {
    private:
        std::vector<std::unique_ptr<UIElement>> m_elements{};

    protected:
        /**
         * construct the element T with parameters Args... and emplaced it into the elements vector.
         * all empaced elements will be checked, updated, rendered and resized.
         * T needs to be derived from UIElekent.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T Element that will be emplaced into the scene
         * @tparam Args All Types the Element needs to be constructed
         * @param args All Parameters the Elements needs to be constructed
         * @return reference of the constructed element
         */
        template<std::derived_from<UIElement> T, typename... Args>
        T& emplace_element(Args&&... args)
            requires(std::constructible_from<T, Args...>)
        {
            auto elem       = std::make_unique<T>(std::forward<Args>(args)...);
            auto const temp = elem.get();
            m_elements.push_back(std::move(elem));
            return *temp;
        }

    public:
        Callback<Scene const&> on_check{};  ///< contains Scene
        Callback<Scene const&> on_update{}; ///< contains Scene
        Callback<Scene const&> on_render{}; ///< contains Scene
        Callback<Scene const&> on_resize{}; ///< contains Scene

        /**
         * this constructor can do exectly nothing.
         * I need it to be able to add the resolution in the scene_manager.
         *
         * @param resolution current resolution
         */
        explicit Scene(cpt::Vec2_i resolution);
        Scene(Scene const&)            = delete; ///< deleted because it will be used in unique_ptr
        Scene(Scene&&)                 = delete; ///< deleted because it will be used in unique_ptr
        Scene& operator=(Scene const&) = delete; ///< deleted because it will be used in unique_ptr
        Scene& operator=(Scene&&)      = delete; ///< deleted because it will be used in unique_ptr
        /**
         * default virtual constructor because of polimorphism.
         */
        virtual ~Scene()               = default;

        /**
         * checking all elements in the scene. provides the context.
         * override this when the derived scene has to check additional stuff.
         * make shure to call Scene::check() and use the return bool.
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep checking
         */
        [[nodiscard]] virtual bool check(Context const& context) const;
        /**
         * updating all elements in the scene. provides the context.
         *
         * override this when the derived scene has to update additional stuff.
         * make shure to call Scene::update() and use the return bool.
         *
         * @param context all changes of the last frame
         * @return whether the next scene should keep updating
         */
        [[nodiscard]] virtual bool update(Context const& context) const;
        /**
         * rendering all elements in the scene. provides the context.
         *
         * override this when the derived scene has to render additional stuff.
         * make shure to call Scene::render().
         *
         * @param context all changes of the last frame
         */
        virtual void render(Context const& context) const;
        /**
         * resizing all elements in the scene. provides the context.
         *
         * override this when the derived scene has to resize additional stuff.
         * make shure to call Scene::resize().
         *
         * @param context all changes of the last frame
         */
        virtual void resize(Context const& context) const;
    };
}; // namespace uil
