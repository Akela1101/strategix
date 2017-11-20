include(cmake/common.cmake)
project(strategix)

file(GLOB_RECURSE SOURCES *.cpp *.cxx *.cc *.C *.c *.h *.hpp)


add_library(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PUBLIC
        src
        ../../easyloggingpp/src)

target_link_libraries(${PROJECT_NAME} nya)

if (COMMAND cotire)
    cotire(${PROJECT_NAME})
endif()