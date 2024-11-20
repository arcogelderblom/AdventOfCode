include_directories(include)

add_library(Day02Lib src/PasswordValidator.cpp)

add_executable(Day02 src/main.cpp)
target_link_libraries(Day02 AoC_GenericLib_static Day02Lib)

add_executable(Day02Test src/test.cpp)
target_link_libraries(Day02Test Day02Lib)