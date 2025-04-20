add_executable(program
        temp.cpp

        input_test_scene.hpp
        input_test_scene.cpp

        music_test_scene.hpp
        music_test_scene.cpp
)

target_include_directories(program
        PUBLIC include
)

target_link_libraries(program
        PRIVATE
        ui_lib_project_options
        ui_lib
)
