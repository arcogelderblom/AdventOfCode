include_directories(include)

add_library(Day05Lib src/BoardingPassScanner.cpp)

add_executable(Day05 src/main.cpp)
target_link_libraries(Day05 AoC_GenericLib_static Day05Lib)

add_executable(Day05Test src/test.cpp)
target_link_libraries(Day05Test Day05Lib)