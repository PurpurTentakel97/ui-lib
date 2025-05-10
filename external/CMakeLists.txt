include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)


CPMAddPackage(
        NAME raylib
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
        OPTIONS
        "BUILD_EXAMPLES OFF"
)

CPMAddPackage(
        NAME cpt-lib
        GITHUB_REPOSITORY PurpurTentakel97/cpt-lib
        GIT_TAG v1.2.1
)

if (cpt__ui_lib_enable_tests)
    CPMAddPackage(
            NAME GOOGLE_TEST
            GITHUB_REPOSITORY google/googletest
            VERSION 1.14.0
            OPTIONS
            "BUILD_GMOCK OFF"
            "INSTALL_GTEST OFF"
    )
endif ()
