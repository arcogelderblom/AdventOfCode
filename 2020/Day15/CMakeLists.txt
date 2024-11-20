include_directories(include)

add_library(Day15Lib src/MemoryGame.cpp)

add_executable(Day15 src/main.cpp)
target_link_libraries(Day15 Day15Lib)
