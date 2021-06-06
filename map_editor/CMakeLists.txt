cmake_minimum_required(VERSION 3.16)
project(map_editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Qt
find_package(Qt5 5.11 REQUIRED Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# common library
set(LIB_NAME map_info)
file(GLOB_RECURSE COMMON_SOURCES map_info/*.cpp map_info/*.h)
add_library(${LIB_NAME} STATIC ${COMMON_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC map_info)
target_link_libraries(${LIB_NAME} strategix Qt5::Widgets)

# application
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${OS_BUNDLE} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src src/forms)
target_link_libraries(${PROJECT_NAME} ${LIB_NAME})

file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)

nya_deploy_qt(${PROJECT_NAME} --no-translations)
