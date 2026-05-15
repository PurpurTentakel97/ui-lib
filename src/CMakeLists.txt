add_library(cpt__ui_lib STATIC)

target_sources(cpt__ui_lib
        PRIVATE
        debug/draw_fps.cpp
        debug/draw_mouse.cpp
        debug/draw_rectangle.cpp

        global/alignment.cpp
        global/app_context.cpp
        global/element.cpp
        global/resolution_enum.cpp
        global/scene.cpp
        global/update_context.cpp
        global/window.cpp

        helper/rect.cpp
        helper/vec.cpp

        system/base_element.cpp
        system/font.cpp
        system/input.cpp
        system/resolution.cpp
        system/sound.cpp
        system/texture.cpp
        system/scene_manager.cpp


        PUBLIC FILE_SET HEADERS
        BASE_DIRS include FILES
        include/uil/debug/basic.hpp
        include/uil/debug/draw_fps.hpp
        include/uil/debug/draw_mouse.hpp
        include/uil/debug/draw_rectangle.hpp

        include/uil/global/app_context.hpp
        include/uil/global/alignment.hpp
        include/uil/global/element.hpp
        include/uil/global/exception.hpp
        include/uil/global/input_enum.hpp
        include/uil/global/resolution_enum.hpp
        include/uil/global/scene.hpp
        include/uil/global/update_context.hpp
        include/uil/global/window.hpp

        include/uil/helper/rect.hpp
        include/uil/helper/vec.hpp

        include/system/base_element.hpp
        include/system/base_manager.hpp
        include/system/font.hpp
        include/system/input.hpp
        include/system/resolution.hpp
        include/system/sound.hpp
        include/system/scene_manager.hpp
        include/system/texture.hpp

        include/system/debug/window.hpp
        include/system/debug/element.hpp
)

target_include_directories(cpt__ui_lib
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(cpt__ui_lib
        PUBLIC
        cpt__cpt_lib
        raylib
        PRIVATE
        $<BUILD_INTERFACE:cpt__ui_lib_project_options>
)

target_link_libraries(raylib INTERFACE glfw) # somehow raylib is not providing glfw at version 5.5 with vcpkg
