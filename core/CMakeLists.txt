include(cmake/common.cmake)
project(strategix)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)


add_library(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_include_directories(${PROJECT_NAME} PUBLIC src ../../easyloggingpp/src)
target_link_libraries(${PROJECT_NAME} nya)
if(MINGW)
    target_link_libraries(${PROJECT_NAME} ws2_32) # boost::asio
endif()

if (COMMAND cotire)
    cotire(${PROJECT_NAME})
endif()