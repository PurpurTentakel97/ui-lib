add_library(ui_lib STATIC)

target_sources(ui_lib
               PRIVATE
               alignment.cpp
               element.cpp
               h_rect.cpp
               h_vec.cpp
               resolution.cpp
               scene.cpp
               scene_manager.cpp
               text.cpp
               window.cpp
               test_scene.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/uil/alignment.hpp
               include/uil/callback.hpp
               include/uil/context.hpp
               include/uil/element.hpp
               include/uil/exception.hpp
               include/uil/h_rect.hpp
               include/uil/h_vec.hpp
               include/uil/resolution.hpp
               include/uil/scene.hpp
               include/uil/scene_manager.hpp
               include/uil/text.hpp
               include/uil/window.hpp
               include/uil/test_scene.hpp
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
