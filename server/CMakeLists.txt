cmake_minimum_required(VERSION 3.9)
project(strategix_s)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Boost
find_package(Boost COMPONENTS system filesystem REQUIRED)


file(GLOB_RECURSE SOURCES *.cpp *.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME}
        strategix
        easyloggingpp
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})


file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
file(COPY maps/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/maps)
