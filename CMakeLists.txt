cmake_minimum_required(VERSION 3.16)
project(strategix_all)

# nya_fetch
file(DOWNLOAD "https://raw.githubusercontent.com/Akela1101/nya/master/cmake/nya_fetch.cmake" "${CMAKE_BINARY_DIR}/nya_fetch.cmake")
include(${CMAKE_BINARY_DIR}/nya_fetch.cmake)

# nya
nya_fetch(git@github.com:Akela1101/nya.git)
include(${FETCH_ROOT}/cmake/nya.cmake)

# add to nya_qt
function(nya_deploy_qt target)
    if(NOT WIN32)
        return()
    endif()

    find_program(windeployqt_exe windeployqt)
    if(NOT windeployqt_exe)
        message(FATAL_ERROR "windeployqt not found. Please, check CMAKE_PREFIX_PATH.")
    endif()

    add_custom_target(${target}-with-qt ALL
            ${windeployqt_exe} ${ARGN} $<TARGET_FILE:${target}>
            DEPENDS ${target}
    )
endfunction()

# easylogging
nya_fetch(git@github.com:amrayn/easyloggingpp.git)
target_include_directories(easyloggingpp SYSTEM PUBLIC ${FETCH_ROOT}/src)

# strategix
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(map_editor)

# samples
add_subdirectory(sample1) #EXCLUDE_FROM_ALL


# verbose output
#set(CMAKE_VERBOSE_MAKEFILE ON)
