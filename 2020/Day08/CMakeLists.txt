include_directories(include)

add_library(Day08Lib src/GameConsole.cpp)

add_executable(Day08 src/main.cpp)
target_link_libraries(Day08 AoC_GenericLib_static Day08Lib)