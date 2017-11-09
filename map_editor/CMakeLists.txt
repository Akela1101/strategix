project(map_editor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories(../../nya/src src src/forms)


# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets)

# compile
add_executable(${PROJECT_NAME}
        src/forms/DialogNew.cpp
        src/forms/DialogNew.h
        src/forms/MainForm.cpp
        src/forms/MainForm.h
        src/MapArea.cpp
        src/MapArea.h
        src/MapInfo.cpp
        src/MapInfo.h
        src/main.cpp)

# link
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

file(COPY config/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)