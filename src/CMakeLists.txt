add_library(ui_lib
            include/uil/test.hpp
            test.cpp
)

target_include_directories(ui_lib
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PUBLIC $<INSTALL_INTERFACE:include>
)

target_link_libraries(ui_lib
                      PRIVATE
                      $<BUILD_INTERFACE:ui_lib_project_options>
)

install(TARGETS ui_lib
        EXPORT ui-lib-targets
)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        FILES_MATCHING PATTERN "*.hpp"
)
