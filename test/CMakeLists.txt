add_executable(lib_tests
               test_alignment.cpp
               test_callbacks.cpp
               test_window.cpp
)

target_link_libraries(lib_tests
                      PRIVATE
                      ui_lib_project_options
                      ui_lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_tests)