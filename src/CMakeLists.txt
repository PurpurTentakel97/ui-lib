add_library(cpt__ui_lib STATIC)

target_sources(cpt__ui_lib
        PRIVATE
        global/app_context.cpp
        global/asset.cpp
        global/font.cpp
        global/input.cpp
        global/resolution.cpp
        global/resolution_enum.cpp
        global/sound.cpp

        helper/rect.cpp
        helper/vec.cpp

        alignment.cpp
        base_element.cpp
        element.cpp
        scene.cpp
        scene_manager.cpp
        update_context.cpp
        window.cpp


        PUBLIC FILE_SET HEADERS
        BASE_DIRS include FILES
        include/uil/debug/basic.hpp
        include/uil/global/app_context.hpp
        include/uil/global/asset.hpp
        include/uil/global/font.hpp
        include/uil/global/input.hpp
        include/uil/global/input_enum.hpp
        include/uil/global/resolution.hpp
        include/uil/global/resolution_enum.hpp
        include/uil/global/sound.hpp

        include/uil/helper/rect.hpp
        include/uil/helper/vec.hpp

        include/uil/alignment.hpp
        include/uil/base_element.hpp
        include/uil/base_manager.hpp
        include/uil/callback.hpp
        include/uil/element.hpp
        include/uil/exception.hpp
        include/uil/scene.hpp
        include/uil/scene_manager.hpp
        include/uil/update_context.hpp
        include/uil/window.hpp
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
