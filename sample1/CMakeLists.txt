project(sample1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(
        src
        ../core/src
        ../../nya/src)

add_executable(${PROJECT_NAME}
        src/AiPlayerSlot.cpp
        src/AiPlayerSlot.h
        src/ConfigurationBuilderFromXml.cpp
        src/ConfigurationBuilderFromXml.h
        src/EntiInfoMesh.h
        src/FrameListenerKernelSlot.cpp
        src/FrameListenerKernelSlot.h
        src/Main.cpp
        src/ResourceInfoMesh.h
        src/Sample1_Forward.h
        src/TechTreesBuilderFromXml.cpp
        src/TechTreesBuilderFromXml.h)


target_link_libraries(${PROJECT_NAME}
        strategix
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})

file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
file(COPY maps/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/maps)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()