set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        physfs.cpp
        window.cpp
        shader.cpp
        shader_globals.cpp
        dynamic_draw_shader.cpp
        vertex_array.cpp
        image.cpp
        sprite_shader.cpp
        texture.cpp
        texture_loader.cpp
        renderer.cpp
        engine.cpp
        main.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE SOL_ALL_SAFETIES_ON=1)

target_link_libraries(${PROJECT_NAME} glad glfw glm imgui lua physfs-static sol2 spdlog stb)