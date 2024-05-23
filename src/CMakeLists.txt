add_library(ui_lib STATIC)

target_sources(ui_lib
               PRIVATE
               alignment.cpp
               ui_element.cpp
               window.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/uil/alignment.hpp
               include/uil/callback.hpp
               include/uil/exception.hpp
               include/uil/resolution.hpp
               include/uil/scene.hpp
               include/uil/ui_element.hpp
               include/uil/utils.hpp
               include/uil/window.hpp



)

target_include_directories(ui_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(ui_lib
                      PUBLIC
                      cpt::cpt-lib
                      PRIVATE
                      raylib
                      $<BUILD_INTERFACE:ui_lib_project_options>
)
