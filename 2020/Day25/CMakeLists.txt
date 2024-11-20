include_directories(include)

add_library(Day25Lib src/Crypto.cpp)

add_executable(Day25 src/main.cpp)
target_link_libraries(Day25 AoC_GenericLib_static Day25Lib)
