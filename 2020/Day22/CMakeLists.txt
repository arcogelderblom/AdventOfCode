include_directories(include)

add_library(Day22Lib src/CombatGame.cpp src/Player.cpp src/RecursiveCombatGame.cpp)

add_executable(Day22 src/main.cpp)
target_link_libraries(Day22 AoC_GenericLib_static Day22Lib)
