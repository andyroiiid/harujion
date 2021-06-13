//
// Created by andyroiiid on 6/13/2021.
//

#include "renderer.h"

#include <spdlog/spdlog.h>
#include <sol/sol.hpp>

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

    vao.setData(
            {
                    {glm::vec2{-0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}, glm::vec4{1.0f, 0.0f, 0.0f, 1.0f}},
                    {glm::vec2{0.5f, -0.5f},  glm::vec2{1.0f, 0.0f}, glm::vec4{0.0f, 1.0f, 0.0f, 1.0f}},
                    {glm::vec2{0.0f, 0.5f},   glm::vec2{0.5f, 1.0f}, glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}}
            },
            GL_STATIC_DRAW
    );
}

void Renderer::update() {
    int w = 0, h = 0;
    window.getFramebufferSize(&w, &h);
    glViewport(0, 0, w, h);
}

void Renderer::clear() {
    glClearBufferfv(GL_COLOR, 0, clearColor);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

void Renderer::test() {
    shader.use();
    vao.bindAndDraw();
    glBindVertexArray(0);
    glUseProgram(0);
}

sol::table Renderer::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table.set_function("setClearColor", [this](float r, float g, float b, float a) { setClearColor(r, g, b, a); });
    table.set_function("test", [this]() { test(); });
    return table;
}
