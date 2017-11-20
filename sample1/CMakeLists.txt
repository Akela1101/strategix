include(../core/cmake/common.cmake)
project(sample1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

find_package(Boost COMPONENTS system filesystem REQUIRED)


file(GLOB_RECURSE SOURCES *.cpp *.cxx *.cc *.C *.c *.h *.hpp)


add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME}
        strategix
        easyloggingpp
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})

if (COMMAND cotire)
    cotire(${PROJECT_NAME})
endif()



file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
file(COPY maps/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/maps)
