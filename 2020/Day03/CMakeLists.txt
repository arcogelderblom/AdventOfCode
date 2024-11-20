include_directories(include)

add_library(Day03Lib src/TobogganRide.cpp)

add_executable(Day03 src/main.cpp)
target_link_libraries(Day03 AoC_GenericLib_static Day03Lib)