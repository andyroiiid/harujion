//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_VERTEX_ARRAY_H
#define HARUJION_VERTEX_ARRAY_H

#include <glad/gl.h>

#include "non_copyable.h"
#include "vertex.h"

class VertexArray : NonCopyable {
public:
    VertexArray();

    ~VertexArray();

    void setData(std::initializer_list<Vertex> vertices, GLenum usage);

    void bindAndDraw();

private:
    GLuint vbo = 0;
    GLuint vao = 0;

    GLsizei count = 0;
};

#endif //HARUJION_VERTEX_ARRAY_H
