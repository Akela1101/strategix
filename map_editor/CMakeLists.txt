cmake_minimum_required(VERSION 3.9)
project(map_editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Qt
find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# common library
set(LIB_NAME map_info)
file(GLOB_RECURSE COMMON_SOURCES map_info/*.cpp map_info/*.h)
add_library(${LIB_NAME} ${COMMON_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC map_info)
target_link_libraries(${LIB_NAME}
        strategix
        easyloggingpp
        Qt5::Widgets
        )

# application
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src src/forms)
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})

file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
