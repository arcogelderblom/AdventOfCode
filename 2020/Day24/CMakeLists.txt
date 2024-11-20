include_directories(include)

add_library(Day24Lib src/Floor.cpp src/HexTile.cpp)

add_executable(Day24 src/main.cpp)
target_link_libraries(Day24 AoC_GenericLib_static Day24Lib)
