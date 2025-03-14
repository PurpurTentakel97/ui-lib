add_library(ui_lib STATIC)

target_sources(ui_lib
               PRIVATE
               scenes/test_scene.cpp
               elements/link.cpp
               elements/text.cpp
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
               include/uil/scenes/test_scene.hpp
               include/uil/elements/link.hpp
               include/uil/elements/text.hpp
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

target_include_directories(ui_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(ui_lib
                      PUBLIC
                      cpt::cpt-lib
                      raylib
                      PRIVATE
                      $<BUILD_INTERFACE:ui_lib_project_options>
)
