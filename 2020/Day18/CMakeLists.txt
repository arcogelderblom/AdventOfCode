include_directories(include)

add_library(Day18Lib src/Calculator.cpp)

add_executable(Day18 src/main.cpp)
target_link_libraries(Day18 AoC_GenericLib_static Day18Lib)
