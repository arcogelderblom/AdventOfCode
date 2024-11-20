include_directories(include)

add_library(Day12Lib src/NavigationComputer.cpp)

add_executable(Day12 src/main.cpp)
target_link_libraries(Day12 AoC_GenericLib_static Day12Lib)

add_executable(Day12Test src/test.cpp)
target_link_libraries(Day12Test AoC_GenericLib_static Day12Lib)
