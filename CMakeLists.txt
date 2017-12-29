cmake_minimum_required(VERSION 3.9)
project(strategix_all)

include(../nya/cmake/nya.cmake)

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
add_subdirectory(../nya nya)

# easylogging
add_subdirectory(../easyloggingpp el)

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
