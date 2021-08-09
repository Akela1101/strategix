cmake_minimum_required(VERSION 3.16)
project(strategix)

# Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.67 REQUIRED filesystem serialization
		# transitive
		date_time regex)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp strx/*.hpp)

add_library(${PROJECT_NAME} STATIC ${sources})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} INTERFACE .)
target_link_libraries(${PROJECT_NAME}
		nya
		easyloggingpp
		Boost::boost
		Boost::filesystem
		Boost::serialization
		Boost::date_time
		Boost::regex
)
# boost::asio
if(WIN32)
	target_link_libraries(${PROJECT_NAME} ws2_32 wsock32)
else()
	find_library(PTHREAD_LIBRARY pthread)
	target_link_libraries(${PROJECT_NAME} ${PTHREAD_LIBRARY})
endif()
