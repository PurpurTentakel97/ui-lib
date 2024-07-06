add_executable(program
               temp.cpp
)

target_include_directories(program
                           PUBLIC include
)

target_link_libraries(program
                      PRIVATE
                      ui_lib_project_options
                      ui_lib
)