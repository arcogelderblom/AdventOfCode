include_directories(include)

add_library(Day07Lib src/LuggageProcessor.cpp src/Bag.cpp)

add_executable(Day07 src/main.cpp)
target_link_libraries(Day07 AoC_GenericLib_static Day07Lib)

add_executable(Day07Test src/test.cpp)
target_link_libraries(Day07Test Day07Lib)