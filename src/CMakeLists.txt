target_sources(${PROJECT_NAME} PRIVATE
        physfs.cpp
        window.cpp
        renderer/shader.cpp
        renderer/shader_globals.cpp
        renderer/dynamic_draw_shader.cpp
        renderer/vertex_array.cpp
        renderer/image.cpp
        renderer/texture.cpp
        renderer/texture_loader.cpp
        renderer/sprite/sprite_shader.cpp
        renderer/sprite/sprite_vertices.cpp
        renderer/sprite/sprite.cpp
        renderer/sprite/sprite_font.cpp
        renderer/tile/tileset.cpp
        renderer/renderer.cpp
        keyboard.cpp
        mouse.cpp
        fmod_audio.cpp
        engine.cpp
        main.cpp)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE SOL_ALL_SAFETIES_ON=1 SOL_LUAJIT=1)

target_link_libraries(${PROJECT_NAME} glad glfw glm imgui luajit physfs-static sol2 spdlog stb fmodstudio)