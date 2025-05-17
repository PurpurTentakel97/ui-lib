include(${CMAKE_SOURCE_DIR}/cmake/warnings.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/sanitizers.cmake)

# the following function was taken from:
# https://github.com/cpp-best-practices/cmake_template/blob/main/ProjectOptions.cmake
macro(check_sanitizer_support)
    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
        set(supports_ubsan ON)
    else ()
        set(supports_ubsan OFF)
    endif ()

    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
        set(supports_asan OFF)
    else ()
        set(supports_asan ON)
    endif ()
endmacro()

check_sanitizer_support()

if (PROJECT_IS_TOP_LEVEL)
    option(cpt__ui_lib_enable_warnings_as_errors "Treat warnings as errors" ON)
    option(cpt__ui_lib_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" ${supports_ubsan})
    option(cpt__ui_lib_enable_address_sanitizer "Enable address sanitizer" OFF) # turn asan off because of runtime issues
    option(cpt__ui_lib_enable_tests "Build tests using Google Test" ON)
    option(cpt__ui_lib_enable_test_programm "Build tests programm to test the lib" ON)
else ()
    option(cpt__ui_lib_enable_warnings_as_errors "Treat warnings as errors" OFF)
    option(cpt__ui_lib_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" OFF)
    option(cpt__ui_lib_enable_address_sanitizer "Enable address sanitizer" OFF)
    option(cpt__ui_lib_enable_tests "Build tests using Google Test" OFF)
    option(cpt__ui_lib_enable_test_programm "Build tests programm to test the lib" OFF)
endif ()

add_library(cpt__ui_lib_warnings INTERFACE)
set_warnings(cpt__ui_lib_warnings ${cpt__ui_lib_enable_warnings_as_errors})

add_library(cpt__ui_lib_sanitizers INTERFACE)
enable_sanitizers(cpt__ui_lib_sanitizers ${cpt__ui_lib_enable_address_sanitizer} ${cpt__ui_lib_enable_undefined_behavior_sanitizer})

add_library(cpt__ui_lib_project_options INTERFACE)
target_link_libraries(cpt__ui_lib_project_options
                      INTERFACE cpt__ui_lib_warnings
                      INTERFACE cpt__ui_lib_sanitizers
)
