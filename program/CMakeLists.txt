add_executable(cpt__ui_lib_program
        temp.cpp

        asset_test_scene.hpp
        asset_test_scene.cpp

        input_test_scene.hpp
        input_test_scene.cpp

        music_test_scene.hpp
        music_test_scene.cpp

        font_test_scene.hpp
        font_test_scene.cpp
)

target_include_directories(cpt__ui_lib_program
        PUBLIC include
)

target_link_libraries(cpt__ui_lib_program
        PRIVATE
        cpt__ui_lib_project_options
        cpt__ui_lib
)
