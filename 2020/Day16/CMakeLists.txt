include_directories(include)

add_library(Day16Lib src/TicketProcessor.cpp)

add_executable(Day16 src/main.cpp)
target_link_libraries(Day16 AoC_GenericLib_static Day16Lib)
