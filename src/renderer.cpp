//
// Created by andyroiiid on 6/13/2021.
//

#include "renderer.h"

#include <spdlog/spdlog.h>
#include <sol/sol.hpp>
#include <glm/gtc/type_ptr.hpp>

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
}

void Renderer::update() {
    int w = 0, h = 0;
    window.getFramebufferSize(&w, &h);
    glViewport(0, 0, w, h);
}

void Renderer::clear() {
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(clearColor));
}

sol::table Renderer::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table.set_function(
            "setClearColor",
            sol::overload(
                    [this](float r, float g, float b) { setClearColor(r, g, b); },
                    [this](float r, float g, float b, float a) { setClearColor(r, g, b, a); }
            )
    );
    table.set_function(
            "setDrawColor",
            sol::overload(
                    [this](float r, float g, float b) { setDrawColor(r, g, b); },
                    [this](float r, float g, float b, float a) { setDrawColor(r, g, b, a); }
            )
    );
    table.set_function(
            "drawPoint",
            sol::overload(
                    [this](float x, float y) { drawPoint(x, y); },
                    [this](float x, float y, float size) { drawPoint(x, y, size); }
            )
    );
    table.set_function(
            "drawLine",
            sol::overload(
                    [this](float x0, float y0, float x1, float y1) { drawLine(x0, y0, x1, y1); },
                    [this](float x0, float y0, float x1, float y1, float width) { drawLine(x0, y0, x1, y1, width); }
            )
    );
    return table;
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    clearColor = {r, g, b, a};
}

void Renderer::setDrawColor(float r, float g, float b, float a) {
    drawColor = {r, g, b, a};
}

void Renderer::dynamicDraw(std::initializer_list<Vertex> vertices, GLenum mode) {
    shader.use();
    vao.setData(vertices, GL_DYNAMIC_DRAW);
    vao.bindAndDraw(mode);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::drawPoint(float x, float y) {
    static constexpr glm::vec2 texCoord{0.0f, 0.0f};
    dynamicDraw(
            {
                    dynamicDrawVertex(x, y)
            },
            GL_POINTS
    );
}

void Renderer::drawPoint(float x, float y, float size) {
    glPointSize(size);
    drawPoint(x, y);
    glPointSize(1.0f);
}

void Renderer::drawLine(float x0, float y0, float x1, float y1) {
    static constexpr glm::vec2 texCoord{0.0f, 0.0f};
    dynamicDraw(
            {
                    dynamicDrawVertex(x0, y0),
                    dynamicDrawVertex(x1, y1)
            },
            GL_LINES
    );
}

void Renderer::drawLine(float x0, float y0, float x1, float y1, float width) {
    glLineWidth(width);
    drawLine(x0, y0, x1, y1);
    glLineWidth(1.0f);
}
