cmake_minimum_required(VERSION 3.11)
project(strategix)

# Boost
SET(Boost_USE_STATIC_LIBS ON CACHE STRING "ON or OFF")
find_package(Boost COMPONENTS date_time filesystem regex serialization system REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC src ${Boost_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} nya easyloggingpp ${Boost_LIBRARIES})
if(WIN32)
	target_link_libraries(${PROJECT_NAME} ws2_32 wsock32) # boost::asio
endif()

if (COMMAND cotire)
	cotire(${PROJECT_NAME})
endif()
