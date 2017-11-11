cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") # disable all warnings!
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif(MSVC)


add_subdirectory(core)
add_subdirectory(map_editor)

add_subdirectory(sample1 EXCLUDE_FROM_ALL)