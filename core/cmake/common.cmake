cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif(MSVC)
add_definitions(-DBOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

# set(CMAKE_VERBOSE_MAKEFILE ON)