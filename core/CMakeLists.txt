cmake_minimum_required(VERSION 3.10)
project(strategix)

# Boost
find_package(Boost COMPONENTS system filesystem serialization REQUIRED)


file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC src ../../easyloggingpp/src)
target_link_libraries(${PROJECT_NAME} nya easyloggingpp ${Boost_LIBRARIES})
if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32 wsock32) # boost::asio
endif()

if (COMMAND cotire)
    cotire(${PROJECT_NAME})
endif()
