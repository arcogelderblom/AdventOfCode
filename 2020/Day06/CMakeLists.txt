include_directories(include)

add_library(Day06Lib src/FormsProcessor.cpp)

add_executable(Day06 src/main.cpp)
target_link_libraries(Day06 AoC_GenericLib_static Day06Lib)

add_executable(Day06Test src/test.cpp)
target_link_libraries(Day06Test Day06Lib)