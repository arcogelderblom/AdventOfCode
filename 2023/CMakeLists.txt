cmake_minimum_required(VERSION 3.22)

project(AdventOfCode2023)

set(CMAKE_CXX_STANDARD 14)

include_directories(../GenericLib/include)
link_directories(../GenericLib/lib)

if (DEFINED AOC_DAY)
    add_subdirectory(${AOC_DAY})
else()
    set(AOC_DAYS Day01;Day02;Day03;Day04;Day05)
    foreach(DAY IN ITEMS ${AOC_DAYS})
        add_subdirectory(${DAY})
    endforeach()
endif()
