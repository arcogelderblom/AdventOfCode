cmake_minimum_required(VERSION 3.22)

project(AdventOfCode_GenericLib)

set(CMAKE_CXX_STANDARD 14)

set(AoC_GenericLib_SOURCES src/FileHandler.cpp 
                           src/StringParser.cpp)

include_directories(include)

add_library(AoC_GenericLib_static STATIC ${AoC_GenericLib_SOURCES})

# add_library(AoC_GenericLib SHARED ${AoC_GenericLib_SOURCES})

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS AoC_GenericLib_static)
