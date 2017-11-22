include(../core/cmake/common.cmake)
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

set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${LIB_NAME} PUBLIC map_info)
target_link_libraries(${LIB_NAME} Qt5::Widgets strategix easyloggingpp)


# application
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PRIVATE src src/forms)
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})

file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)
