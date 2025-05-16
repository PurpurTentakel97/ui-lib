include_guard(GLOBAL)
include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage(
        NAME cpt-lib
        GITHUB_REPOSITORY PurpurTentakel97/cpt-lib
        GIT_TAG v1.2.1
)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED) # somehow raylib does not provide glfw at version 5.5 with vcpkg

if (cpt__ui_lib_enable_tests)
    find_package(GTest CONFIG REQUIRED)
endif ()
