add_library(cpt__ui_lib STATIC)

target_sources(cpt__ui_lib
        PRIVATE
        debug/debug_classes.cpp

        elements/link.cpp
        elements/text.cpp

        global/app_context.cpp
        global/input.cpp
        global/sound.cpp

        helper/path.cpp
        helper/rect.cpp
        helper/vec.cpp

        alignment.cpp
        base_element.cpp
        context.cpp
        element.cpp
        resolution.cpp
        scene.cpp
        scene_manager.cpp
        window.cpp


        PUBLIC FILE_SET HEADERS
        BASE_DIRS include FILES
        include/uil/debug/debug.hpp
        include/uil/debug/debug_classes.hpp
        include/uil/debug/debug_wrapper.hpp
        include/uil/debug/debug_types.hpp

        include/uil/elements/link.hpp
        include/uil/elements/text.hpp

        include/uil/global/app_context.hpp
        include/uil/global/input.hpp
        include/uil/global/input_enum.hpp
        include/uil/global/sound.hpp

        include/uil/helper/path.hpp
        include/uil/helper/rect.hpp
        include/uil/helper/vec.hpp

        include/uil/alignment.hpp
        include/uil/base_element.hpp
        include/uil/base_manager.hpp
        include/uil/callback.hpp
        include/uil/context.hpp
        include/uil/element.hpp
        include/uil/exception.hpp
        include/uil/resolution.hpp
        include/uil/scene.hpp
        include/uil/scene_manager.hpp
        include/uil/window.hpp
)

target_include_directories(cpt__ui_lib
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_system_libraries(cpt__ui_lib
        PUBLIC
        cpt__cpt_lib
        raylib)
target_link_libraries(cpt__ui_lib
        PRIVATE
        $<BUILD_INTERFACE:cpt__ui_lib_project_options>
)
