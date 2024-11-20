include_directories(include)

add_library(Day11Lib src/FloorPlan.cpp)

add_executable(Day11 src/main.cpp)
target_link_libraries(Day11 AoC_GenericLib_static Day11Lib)

add_executable(Day11Test src/test.cpp)
target_link_libraries(Day11Test AoC_GenericLib_static Day11Lib)
