include_directories(include)

add_library(Day04Lib src/PassportValidator.cpp src/Passport.cpp)

add_executable(Day04 src/main.cpp)
target_link_libraries(Day04 AoC_GenericLib_static Day04Lib)

add_executable(Day04Test src/test.cpp)
target_link_libraries(Day04Test Day04Lib)