cmake_minimum_required(VERSION 3.2)
project(fmod CXX)

add_library(fmod SHARED IMPORTED GLOBAL)
set_target_properties(fmod PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod.dll
        IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmod_vc.lib)
target_include_directories(fmod INTERFACE include)

add_library(fmodstudio SHARED IMPORTED GLOBAL)
set_target_properties(fmodstudio PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmodstudio.dll
        IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/fmodstudio_vc.lib)
target_link_libraries(fmodstudio INTERFACE fmod)