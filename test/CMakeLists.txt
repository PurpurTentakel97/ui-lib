add_executable(lib_tests
               default.cpp
)

target_link_libraries(lib_tests
                      PRIVATE
                      project_options
                      ui_lib
                      GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_tests)