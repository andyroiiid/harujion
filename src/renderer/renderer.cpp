// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/renderer.h"

#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

Renderer &Renderer::getInstance()
{
    static Renderer instance;
    return instance;
}

Renderer::Renderer()
{
#define LOG_GL_STRING(name) spdlog::info(#name ": {}", reinterpret_cast<const char *>(glGetString(name)))
    LOG_GL_STRING(GL_VERSION);
    LOG_GL_STRING(GL_SHADING_LANGUAGE_VERSION);
    LOG_GL_STRING(GL_VENDOR);
    LOG_GL_STRING(GL_RENDERER);
#undef LOG_GL_STRING

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::clear()
{
    auto [width, height] = window.getFramebufferSize();
    glViewport(0, 0, width, height);
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(clearColor));
}

void Renderer::setMatrixOrtho(float left, float right, float bottom, float top)
{
    shaderGlobals.setMatrix(glm::ortho(left, right, bottom, top));
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    clearColor = {r, g, b, a};
}

void Renderer::setDrawColor(float r, float g, float b, float a)
{
    drawColor = {r, g, b, a};
}

inline Vertex Renderer::dynamicDrawVertex(float x, float y)
{
    return Vertex {
        glm::vec2 {   x,    y},
         glm::vec2 {0.0f, 0.0f},
         drawColor
    };
}

void Renderer::dynamicDraw(std::initializer_list<Vertex> vertices, GLenum mode)
{
    dynamicDrawShader.use();
    dynamicDrawVao.setData(vertices, GL_DYNAMIC_DRAW);
    dynamicDrawVao.bindAndDraw(mode);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::drawPoint(float x, float y)
{
    dynamicDraw(
        {
            dynamicDrawVertex(x, y),
        },
        GL_POINTS
    );
}

void Renderer::drawPoint(float x, float y, float size)
{
    glPointSize(size);
    drawPoint(x, y);
    glPointSize(1.0f);
}

void Renderer::drawLine(float x0, float y0, float x1, float y1)
{
    dynamicDraw(
        {
            dynamicDrawVertex(x0, y0),
            dynamicDrawVertex(x1, y1),
        },
        GL_LINES
    );
}

void Renderer::drawLine(float x0, float y0, float x1, float y1, float width)
{
    glLineWidth(width);
    drawLine(x0, y0, x1, y1);
    glLineWidth(1.0f);
}

void Renderer::drawRect(float x0, float y0, float x1, float y1)
{
    dynamicDraw(
        {
            dynamicDrawVertex(x0, y0),
            dynamicDrawVertex(x1, y0),
            dynamicDrawVertex(x1, y1),
            dynamicDrawVertex(x0, y1),
        },
        GL_LINE_LOOP
    );
}

void Renderer::drawRect(float x0, float y0, float x1, float y1, float width)
{
    glLineWidth(width);
    drawRect(x0, y0, x1, y1);
    glLineWidth(1.0f);
}

void Renderer::fillRect(float x0, float y0, float x1, float y1)
{
    dynamicDraw(
        {
            dynamicDrawVertex(x0, y0),
            dynamicDrawVertex(x1, y0),
            dynamicDrawVertex(x0, y1),
            dynamicDrawVertex(x1, y1),
        },
        GL_TRIANGLE_STRIP
    );
}
