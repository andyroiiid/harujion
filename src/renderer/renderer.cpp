//
// Created by andyroiiid on 6/13/2021.
//

#include "renderer/renderer.h"

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetFramebufferSizeCallback(window.window, [](GLFWwindow *_, int width, int height) {
        auto &renderer = Renderer::getInstance();
        renderer.framebufferResize(width, height);
    });
    {
        int width, height;
        window.getFramebufferSize(&width, &height);
        framebufferResize(width, height);
    }
}

void Renderer::framebufferResize(int width, int height) {
    glViewport(0, 0, width, height);
    camera.framebufferResize(width, height);
}

void Renderer::update() {
    shaderGlobals.setMatrix(camera.getMatrix());
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
            "setCameraHalfHeight",
            [this](float halfHeight) { camera.setHalfHeight(halfHeight); }
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

inline Vertex Renderer::dynamicDrawVertex(float x, float y) {
    return Vertex{glm::vec2{x, y}, glm::vec2{0.0f, 0.0f}, drawColor};
}

void Renderer::dynamicDraw(std::initializer_list<Vertex> vertices, GLenum mode) {
    dynamicDrawShader.use();
    dynamicDrawVao.setData(vertices, GL_DYNAMIC_DRAW);
    dynamicDrawVao.bindAndDraw(mode);
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
