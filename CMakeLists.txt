cmake_minimum_required(VERSION 3.9)

# Common stuff
add_subdirectory(../nya nya)

# Easylogging
set(build_static_lib ON cache)
add_subdirectory(../easyloggingpp easyloggingpp)
target_compile_definitions(easyloggingpp PRIVATE ELPP_NO_DEFAULT_LOG_FILE)

# Strategix
add_subdirectory(core)
add_subdirectory(map_editor)

add_subdirectory(sample1 EXCLUDE_FROM_ALL)