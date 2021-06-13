cmake_minimum_required(VERSION 3.19)
project(harujion)

add_subdirectory(dependencies EXCLUDE_FROM_ALL)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE include)