cmake_minimum_required(VERSION 3.0)
project(glad C)

add_library(glad src/gl.c)

target_include_directories(glad PUBLIC include)