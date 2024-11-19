cmake_minimum_required(VERSION 3.22)

project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 23)

include_directories(../GenericLib/include)
link_directories(../GenericLib/lib)

if (DEFINED AOC_DAY)
    add_subdirectory(${AOC_DAY})
else()
    set(AOC_DAYS Day01;Day02;Day03;Day04;Day05;Day06;Day07;Day08;Day09;Day10;Day11;Day12;Day13;Day14;Day15;Day16;Day17;Day18;Day19;Day20;Day21;Day22;Day23;Day24;Day25)
    foreach(DAY IN ITEMS ${AOC_DAYS})
        add_subdirectory(${DAY})
    endforeach()
endif()
