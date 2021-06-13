cmake_minimum_required(VERSION 3.2)
project(imgui CXX)

add_library(imgui
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
        imgui_impl_opengl3.cpp
        imgui_impl_glfw.cpp)

target_include_directories(imgui PUBLIC include)

target_link_libraries(imgui glfw glad)
