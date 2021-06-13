set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        physfs.cpp
        window.cpp
        renderer.cpp
        main.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE SOL_ALL_SAFETIES_ON=1)

target_link_libraries(${PROJECT_NAME} glad glfw glm imgui lua physfs-static sol2 spdlog stb)