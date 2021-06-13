cmake_minimum_required(VERSION 3.16)
project(sol2 CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(sol2 INTERFACE)

target_include_directories(sol2 INTERFACE include)