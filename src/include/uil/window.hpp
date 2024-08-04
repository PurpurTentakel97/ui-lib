//
// Purpur Tentakel
// 30.05.24
//

#pragma once
#include <cpt/vec2.hpp>
#include <uil/scene_manager.hpp>

namespace uil {
    struct Context;

    /**
     * provides the construct config for a window.
     * some config need to be set that way because it can only be set bevor the window is initialized.
     */
    struct WindowConfig final {
        bool v_sync            = false;
        bool fullscreen        = false;
        bool resizable         = false;
        bool undecorated       = false;
        bool hidden            = false;
        bool minimized         = false;
        bool maximized         = false;
        bool unfocused         = false;
        bool top_most          = false;
        bool always_run        = false;
        bool transparent       = false;
        bool high_dpi          = false;
        bool mouse_passthrough = false;
        bool borderless_window = false;
        bool msaa              = false;
        bool interlased        = false;
    };

    /**
     * main window of the game.
     * you can only have one instance.
     * add scenes here with emplace.
     */
    class Window final {
    private:
        bool m_draw_fps = true;
        cpt::Vec2_i m_resolution;
        SceneManager m_scene_manager{};
        Font m_font{};

        void update_resolution();
        [[nodiscard]] Context create_context() const;

        static void set_flag(ConfigFlags flag, bool active);

    public:
        /**
         * initializes the window and sets all window flags.
         *
         * @param resolution initial window dimensions
         * @param title window title
         * @param config window state config
         */
        Window(cpt::Vec2_i resolution, char const* title, WindowConfig config);
        Window(Window const&)              = delete; ///< deleted because only one instance is allowed
        Window(Window&& window)            = delete; ///< deleted because not neccecary
        Window& operator=(Window const&)   = delete; ///< deleted because only one instance is allowed
        Window& operator=(Window&& window) = delete; ///< deleted because not neccecary
        /**
         * closes window.
         */
        ~Window();

        /**
         * construct the scene T with parameters Args... and emplaced it into the scene vector.
         * all empaced scenes will be checked, updated, rendered and resized.
         *
         * T needs to be derived from Scene.
         * T needs to be constructable with parameters Args...
         *
         * @tparam T acene that will be emplaced into the scene_manager
         * @tparam Args all Types the scene needs to be constructed
         * @param args all Parameters the scene needs to be constructed
         * @return reference of the constructed scene
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_back(Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return m_scene_manager.emplace_back<T>(m_resolution, args...);
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
         * @return pointer of the constructed scene
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_front(Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return m_scene_manager.emplace_front<T>(m_resolution, args...);
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
         * @return pointer of the constructed scene
         * @throw BadSceneIndex will throw when index is out of range
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_at(cpt::usize const index, Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return m_scene_manager.emplace_at<T>(index, m_resolution, args...);
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
         * @param before proviedes the scene pointer the new scene gets emplaced before
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         * @throw BadScenePointer throws when provided before scene can not be fount in the scenes vector
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_after(Scene const* before, Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return m_scene_manager.emplace_after<T>(before, m_resolution, args...);
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
         * @param after proviedes the scene pointer the new scene gets emplaced after
         * @param args all Parameters the scene needs to be constructed
         * @return pointer of the constructed scene
         * @throw BadScenePointer throws when provided after scene can not be found in the scenes vector
         */
        template<std::derived_from<Scene> T, typename... Args>
        T* emplace_before(Scene const* after, Args... args)
            requires(std::constructible_from<T, cpt::Vec2_i, Args...>)
        {
            return m_scene_manager.emplace_before<T>(after, m_resolution, args...);
        }


        /**
         * Set to try enabling V-Sync on GPU. (raylib)
         *
         * @param vsync defines if vsync is active
         */
        static void set_vsync(bool vsync);
        /**
         * Set to run program in fullscreen. (raylib)
         *
         * @param fullscreen defines if fullscreen is active
         */
        static void set_fullscreen(bool fullscreen);
        /**
         * Set to allow resizable window. (raylib)
         *
         * @param resizeable defines if resizable is active
         */
        static void set_resizeable(bool resizeable);
        /**
         * Set to disable window decoration (frame and buttons). (raylib)
         *
         * @param undecorated defines if undecorated is active
         */
        static void set_undecorated(bool undecorated);
        /**
         * Set to hide window. (raylib)
         *
         * @param hidden defines if hidden is active
         */
        static void set_hidden(bool hidden);
        /**
         * Set to minimize window (iconify). (raylib)
         *
         * @param minimized defines if minimized is active
         */
        static void set_minimized(bool minimized);
        /**
         * Set to maximize window (expanded to monitor). (raylib)
         *
         * @param maximized defines if maximized is active
         */
        static void set_maximized(bool maximized);
        /**
         * Set to window non focused. (raylib)
         *
         * @param unfocused defines if unfocused is active
         */
        static void set_unfocused(bool unfocused);
        /**
         * Set to window always on top. (raylib)
         *
         * @param top_most defines ist top_most is active
         */
        static void set_top_most(bool top_most);
        /**
         *  Set to allow windows running while minimized. (raylib)
         *
         * @param always_run defines if alwayes_run is active
         */
        static void set_always_run(bool always_run);
        /**
         * Set to support mouse passthrough, only supported when set_undecorated(). (raylib)
         *
         * @param mouse_pathrough defines if mouse_pathrough is active
         */
        static void set_mouse_pathrough(bool mouse_pathrough);
        /**
         * Set to run program in borderless windowed mode. (raylib)
         *
         * @param boderless defines if borderless is active
         */
        static void set_boderless(bool boderless);

        /**
         * checks if the provided flag is set or not.
         * use raylib type to check.
         *
         * @param flag Flag you want to check
         * @return if provided flag is true
         */
        [[nodiscard]] static bool is_config_flag(ConfigFlags flag);

        /**
         * creates the context and checks, updates and render the scene manager.
         * renders fps in debug mode when activated.
         *
         */
        void update();

        /**
         * draws current fps at the top left corner if the screen.
         * this only works in debug mode.
         *
         * @param draw_fps defines if draw_fps is active
         */
        void set_draw_fps_debug(bool draw_fps);
        /**
         *
         * @return if are fps currently drawn
         */
        [[nodiscard]] bool draw_fps_debug() const;
    };
} // namespace uil
