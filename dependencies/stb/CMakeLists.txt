cmake_minimum_required(VERSION 3.0)
project(stb C)

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE include)