add_executable(program
               temp.cpp

               test_scene.hpp
               test_scene.cpp
)

target_include_directories(program
                           PUBLIC include
)

target_link_libraries(program
                      PRIVATE
                      ui_lib_project_options
                      ui_lib
)
