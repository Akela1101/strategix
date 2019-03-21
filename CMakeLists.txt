cmake_minimum_required(VERSION 3.14)
project(strategix_all)

# nya_fetch
file(DOWNLOAD "https://raw.githubusercontent.com/Akela1101/nya/master/cmake/nya_fetch.cmake" "${CMAKE_BINARY_DIR}/nya_fetch.cmake")
include(${CMAKE_BINARY_DIR}/nya_fetch.cmake)

# cotire
# -DCMAKE_MODULE_PATH="C:/msys/mingw64/share/cmake/Modules"
# -DCOTIRE_MAXIMUM_NUMBER_OF_UNITY_INCLUDES=-j3
include(cotire OPTIONAL)
set_property(GLOBAL PROPERTY COTIRE_ADD_UNITY_BUILD FALSE) # disable uniting source files into batches, because of add_subdirectory(..
set_property(GLOBAL PROPERTY COTIRE_PREFIX_HEADER_IGNORE_PATH
		"${CMAKE_BINARY_DIR}"
		"${CMAKE_SOURCE_DIR}"
		"${CMAKE_SOURCE_DIR}/../nya") # exclude nya from pch, as it's small and can change frequently

# nya
nya_fetch(git@github.com:Akela1101/nya.git)
include(${FETCH_ROOT}/cmake/nya.cmake)

# easylogging
nya_fetch(git@github.com:zuhd-org/easyloggingpp.git)
target_include_directories(easyloggingpp PUBLIC ${FETCH_ROOT}/src) # + PR in el

# strategix
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(map_editor)

# samples
add_subdirectory(sample1) #EXCLUDE_FROM_ALL


# show all variables
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

# verbose output
#set(CMAKE_VERBOSE_MAKEFILE ON)
