// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/vertex_array.h"

VertexArray::VertexArray()
{
    glCreateBuffers(1, &vbo);

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

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void VertexArray::setData(std::initializer_list<Vertex> vertices, GLenum usage)
{
    count = static_cast<GLsizei>(vertices.size());
    glNamedBufferData(vbo, static_cast<GLsizeiptr>(sizeof(Vertex) * count), vertices.begin(), usage);
}

void VertexArray::bindAndDraw(GLenum mode)
{ // NOLINT(readability-make-member-function-const)
    if (count <= 0)
    {
        return;
    }
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, count);
}
