find_package(Git REQUIRED QUIET)

macro(nya_submodule SUBMODULE_ROOT)
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --rebase ${SUBMODULE_ROOT}
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            RESULT_VARIABLE result)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Failed to update ${SUBMODULE_ROOT}. Please, update manually.")
    endif()

    add_subdirectory(${SUBMODULE_ROOT})
endmacro(nya_submodule)
