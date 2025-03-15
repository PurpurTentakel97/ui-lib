add_executable(lib_tests
               test_alignment_conversion.cpp
               test_alignment_horizontal.cpp
               test_alignment_standard.cpp
               test_alignment_vertical.cpp
               test_callbacks.cpp
               test_exception.cpp
               test_rect.cpp
               test_resolution.cpp
               test_element_text.cpp
               test_vec.cpp
)

target_link_libraries(lib_tests
                      PRIVATE
                      ui_lib_project_options
                      ui_lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_tests)
