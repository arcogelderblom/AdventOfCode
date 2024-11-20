include_directories(include)

add_library(Day20Lib src/ImageTile.cpp src/ImageAssembler.cpp src/ImageProcessor.cpp)

add_executable(Day20 src/main.cpp)
target_link_libraries(Day20 AoC_GenericLib_static Day20Lib)
