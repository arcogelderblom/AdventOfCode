include_directories(include)

add_library(Day19Lib src/MessageProcessor.cpp)

add_executable(Day19 src/main.cpp)
target_link_libraries(Day19 AoC_GenericLib_static Day19Lib)
