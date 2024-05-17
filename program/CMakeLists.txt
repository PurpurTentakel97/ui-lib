add_executable(program
               include/program/temp.hpp
               temp.cpp
)

target_include_directories(program
                           PUBLIC include
)

target_link_libraries(program
                      PRIVATE
                      ui_lib
)