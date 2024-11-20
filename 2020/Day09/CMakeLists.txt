include_directories(include)

add_library(Day09Lib src/XMASEncryptor.cpp)

add_executable(Day09 src/main.cpp)
target_link_libraries(Day09 AoC_GenericLib_static Day09Lib)