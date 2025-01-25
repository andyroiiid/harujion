cmake_minimum_required(VERSION 3.19)
project(harujion)

add_subdirectory(dependencies EXCLUDE_FROM_ALL)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/out)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE include)

add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
)

add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)