// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <glad/gl.h>
#include <initializer_list>

#include "non_copyable.h"
#include "renderer/vertex.h"

class VertexArray : NonCopyable
{
public:
    VertexArray();

    ~VertexArray();

    void setData(std::initializer_list<Vertex> vertices, GLenum usage);

    void bindAndDraw(GLenum mode);

private:
    GLuint vbo = 0;
    GLuint vao = 0;

    GLsizei count = 0;
};
