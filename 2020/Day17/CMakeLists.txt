include_directories(include)

add_library(Day17Lib src/ConwayCubesV1.cpp src/ConwayCubesV2.cpp)

add_executable(Day17 src/main.cpp)
target_link_libraries(Day17 AoC_GenericLib_static Day17Lib)

add_executable(Day17Test src/test.cpp)
target_link_libraries(Day17Test AoC_GenericLib_static Day17Lib)
