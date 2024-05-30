add_library(ui_lib STATIC)

target_sources(ui_lib
               PRIVATE
               alignment.cpp
               helper_rect.cpp
               resolution.cpp
               ui_element.cpp
               update_render_helper.cpp
               scene.cpp
               scene_manager.cpp
               window.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/uil/alignment.hpp
               include/uil/callback.hpp
               include/uil/exception.hpp
               include/uil/helper_rect.hpp
               include/uil/resolution.hpp
               include/uil/scene.hpp
               include/uil/scene_manager.hpp
               include/uil/ui_element.hpp
               include/uil/update_render_helper.hpp
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
