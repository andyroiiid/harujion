//
// Created by andyroiiid on 6/13/2021.
//

#include "renderer.h"

#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

#include "vertex.h"

Renderer &Renderer::getInstance() {
    static Renderer instance;
    return instance;
}

Renderer::Renderer() {
#define LOG_GL_STRING(name) spdlog::info(#name ": {}", glGetString(name))
    LOG_GL_STRING(GL_VERSION);
    LOG_GL_STRING(GL_SHADING_LANGUAGE_VERSION);
    LOG_GL_STRING(GL_VENDOR);
    LOG_GL_STRING(GL_RENDERER);
#undef LOG_GL_STRING

    static const Vertex vertices[] = {
            {glm::vec2{-0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}},
            {glm::vec2{0.5f, -0.5f},  glm::vec2{1.0f, 0.0f}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}},
            {glm::vec2{0.0f, 0.5f},   glm::vec2{0.5f, 1.0f}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}}
    };

    glCreateBuffers(1, &vbo);
    glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, aPosition));

    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribBinding(vao, 1, 0);
    glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, aTexCoord));

    glEnableVertexArrayAttrib(vao, 2);
    glVertexArrayAttribBinding(vao, 2, 0);
    glVertexArrayAttribFormat(vao, 2, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, aColor));
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Renderer::update() {
    int w = 0, h = 0;
    window.getFramebufferSize(&w, &h);
    glViewport(0, 0, w, h);
}

void Renderer::clear() {
    glClearBufferfv(GL_COLOR, 0, clearColor);
}

void Renderer::test() {
    shader.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

sol::table Renderer::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table["clearColor"] = std::ref(clearColor);
    table.set_function("test", [this]() { test(); });
    return table;
}
