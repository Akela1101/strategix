cmake_minimum_required(VERSION 3.16)
project(strategix_all)

include(cmake/utils.cmake)

# nya
nya_submodule(deps/nya)
include(deps/nya/cmake/nya.cmake)

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
nya_submodule(deps/easyloggingpp)
target_include_directories(easyloggingpp SYSTEM PUBLIC deps/easyloggingpp/src)

# strategix
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(map_editor)

# samples
add_subdirectory(sample1) #EXCLUDE_FROM_ALL


# verbose output
#set(CMAKE_VERBOSE_MAKEFILE ON)
