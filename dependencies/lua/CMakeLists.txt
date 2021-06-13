cmake_minimum_required(VERSION 3.0)
project(lua C)

set(CMAKE_C_STANDARD 90)

file(GLOB LUA_SRC src/*.c src/*.h)

add_library(lua ${LUA_SRC})

target_include_directories(lua PUBLIC include)