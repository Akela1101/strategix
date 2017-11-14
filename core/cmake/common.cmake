cmake_minimum_required(VERSION 3.9)

if(MSVC)
    add_compile_options("/std:c++latest")
endif(MSVC)
add_definitions(-DBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

# set(CMAKE_VERBOSE_MAKEFILE ON)