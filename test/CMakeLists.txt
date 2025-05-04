add_executable(cpt__ui_lib_tests
        test_alignment_conversion.cpp
        test_alignment_horizontal.cpp
        test_alignment_standard.cpp
        test_alignment_vertical.cpp
        test_callbacks.cpp
        test_exception.cpp
        test_rect.cpp
        test_resolution.cpp
        test_vec.cpp
)

target_link_libraries(cpt__ui_lib_tests
        PRIVATE
        GTest::gtest_main
)
target_link_libraries(cpt__ui_lib_tests
        PRIVATE
        cpt__ui_lib_project_options
        cpt__ui_lib
)

include(GoogleTest)
gtest_discover_tests(cpt__ui_lib_tests)
