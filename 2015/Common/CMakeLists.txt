add_library(Common inputfile.cpp stringoperations.cpp vectoroperations.cpp)
target_include_directories (Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})