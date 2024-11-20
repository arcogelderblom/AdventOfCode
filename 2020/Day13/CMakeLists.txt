include_directories(include)

add_library(Day13Lib src/BusPlanner.cpp)

add_executable(Day13 src/main.cpp)
target_link_libraries(Day13 AoC_GenericLib_static Day13Lib)
