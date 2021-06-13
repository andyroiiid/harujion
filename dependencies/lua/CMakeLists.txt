cmake_minimum_required(VERSION 3.0)
project(lua CXX)

set(CMAKE_CXX_STANDARD 98)

file(GLOB LUA_SRC src/*.c src/*.h)

add_library(lua ${LUA_SRC})

target_include_directories(lua PUBLIC include)