cmake_minimum_required(VERSION 3.16)
project(strategix_all)

# nya_fetch
file(DOWNLOAD "https://raw.githubusercontent.com/Akela1101/nya/master/cmake/nya_fetch.cmake" "${CMAKE_BINARY_DIR}/nya_fetch.cmake")
include(${CMAKE_BINARY_DIR}/nya_fetch.cmake)

# nya
nya_fetch(git@github.com:Akela1101/nya.git)
include(${FETCH_ROOT}/cmake/nya.cmake)

# easylogging
nya_fetch(git@github.com:zuhd-org/easyloggingpp.git)
target_include_directories(easyloggingpp SYSTEM PUBLIC ${FETCH_ROOT}/src)

# strategix
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(map_editor)

# samples
add_subdirectory(sample1) #EXCLUDE_FROM_ALL


# verbose output
#set(CMAKE_VERBOSE_MAKEFILE ON)
