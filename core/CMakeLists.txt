cmake_minimum_required(VERSION 3.9)
project(strategix)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)


add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src ../../easyloggingpp/src)
target_link_libraries(${PROJECT_NAME} nya)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32 wsock32) # boost::asio
endif()

if (COMMAND cotire)
    cotire(${PROJECT_NAME})
endif()