cmake_minimum_required(VERSION 3.30.3)

project(cpt__ui_lib)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${PROJECT_SOURCE_DIR}/cmake/project_options.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/SystemLink.cmake)
add_subdirectory(external)
add_subdirectory(src bin)

if (cpt__ui_lib_enable_test_programm)
    add_subdirectory(${PROJECT_SOURCE_DIR}/program)
endif ()

if (cpt__ui_lib_enable_tests)
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif ()

install(TARGETS
        cpt__ui_lib
        raylib
        glfw
        EXPORT cpt__ui_lib_targets ARCHIVE
        FILE_SET HEADERS
)
install(EXPORT cpt__ui_lib_targets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
        NAMESPACE cpt::
)
install(FILES "cmake/ui-lib-config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
