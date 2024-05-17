add_library(ui_lib STATIC)

target_sources(ui_lib
               PRIVATE
               temp.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/uil/Callback.hpp
)

target_include_directories(ui_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(ui_lib
                      PUBLIC
                      cpt::cpt_lib
                      PRIVATE
                      $<BUILD_INTERFACE:ui_lib_project_options>
)
