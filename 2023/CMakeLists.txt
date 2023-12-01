cmake_minimum_required(VERSION 3.22)

project(AdventOfCode2023)

set(CMAKE_CXX_STANDARD 14)

include_directories(../GenericLib/include)
link_directories(../GenericLib/lib)

add_subdirectory(${AOC_DAY})
