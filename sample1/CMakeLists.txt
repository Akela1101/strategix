include(../core/cmake/common.cmake)
project(sample1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


find_package(Boost COMPONENTS system filesystem REQUIRED)


add_executable(${PROJECT_NAME}
        src/DefaultPlayerSlot.cpp
        src/DefaultPlayerSlot.h
        src/DefaultKernelSlot.cpp
        src/DefaultKernelSlot.h
        src/Main.cpp
        src/Sample1_Forward.h
        )

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME}
        strategix
        easyloggingpp
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})

file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
file(COPY maps/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/maps)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()