include_directories(include)

add_library(Day23Lib src/Cup.cpp src/CupGame.cpp)

add_executable(Day23 src/main.cpp)
target_link_libraries(Day23 Day23Lib)
