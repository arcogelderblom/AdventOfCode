include_directories(include)

add_library(Day21Lib src/Product.cpp src/GroceryList.cpp)

add_executable(Day21 src/main.cpp)
target_link_libraries(Day21 AoC_GenericLib_static Day21Lib)
