cmake_minimum_required(VERSION 3.5)
project(luajit C)

add_library(luajit SHARED IMPORTED GLOBAL)
set_target_properties(luajit PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/lua51.dll
        IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/lua51.lib)
target_include_directories(luajit INTERFACE include)