add_library(ui_lib)

target_sources(ui_lib
               PRIVATE
               test.cpp

               PUBLIC FILE_SET HEADERS
               BASE_DIRS include FILES
               include/uil/test.hpp
)

target_include_directories(ui_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(ui_lib
                      PUBLIC
                      cpt::cpt-lib
                      PRIVATE
                      $<BUILD_INTERFACE:ui_lib_project_options>
)
