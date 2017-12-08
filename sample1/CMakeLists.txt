include(../core/cmake/common.cmake)
project(sample1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Boost
find_package(Boost COMPONENTS system filesystem REQUIRED)

# Qt
find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


file(GLOB_RECURSE SOURCES *.cpp *.h)
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME}
        strategix
        easyloggingpp
        map_info
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY})


file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
file(COPY ../map_editor/config/map/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config/map)
file(COPY maps/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/maps)
