include_directories(include)

add_library(Day10Lib src/AdapterStacker.cpp)

add_executable(Day10 src/main.cpp)
target_link_libraries(Day10 AoC_GenericLib_static Day10Lib)

add_executable(Day10Test src/test.cpp)
target_link_libraries(Day10Test AoC_GenericLib_static Day10Lib)