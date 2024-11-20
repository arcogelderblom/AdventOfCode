include_directories(include)

add_library(Day14Lib src/Decoder.cpp)

add_executable(Day14 src/main.cpp)
target_link_libraries(Day14 AoC_GenericLib_static Day14Lib)
