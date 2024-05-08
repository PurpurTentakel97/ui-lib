add_library(ui_lib
            STATIC
            include/uil/test.hpp
            test.cpp
)

target_include_directories(ui_lib
                           PRIVATE include/uil
                           INTERFACE include
)

target_link_libraries(ui_lib
                      PRIVATE
                      project_options
)