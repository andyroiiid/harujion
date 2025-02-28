// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include "non_copyable.h"
#include "renderer/dynamic_draw_shader.h"
#include "renderer/shader_globals.h"
#include "renderer/vertex_array.h"
#include "window.h"

class Renderer : NonCopyable
{
public:
    static Renderer &getInstance();

    void clear();

    void setMatrixOrtho(float left, float right, float bottom, float top);

    void setClearColor(float r, float g, float b, float a = 1.0f);

    void setDrawColor(float r, float g, float b, float a = 1.0f);

    void drawPoint(float x, float y);

    void drawPoint(float x, float y, float size);

    void drawLine(float x0, float y0, float x1, float y1);

    void drawLine(float x0, float y0, float x1, float y1, float width);

    void drawRect(float x0, float y0, float x1, float y1);

    void drawRect(float x0, float y0, float x1, float y1, float width);

    void fillRect(float x0, float y0, float x1, float y1);

private:
    Renderer();

    Vertex dynamicDrawVertex(float x, float y);

    void dynamicDraw(std::initializer_list<Vertex> vertices, GLenum mode);

    Window            &window            = Window::getInstance();
    ShaderGlobals     &shaderGlobals     = ShaderGlobals::getInstance();
    DynamicDrawShader &dynamicDrawShader = DynamicDrawShader::getInstance();

    glm::vec4 clearColor = {0.2f, 0.2f, 0.2f, 1.0f};
    glm::vec4 drawColor  = {1.0f, 1.0f, 1.0f, 1.0f};

    VertexArray dynamicDrawVao;
};
