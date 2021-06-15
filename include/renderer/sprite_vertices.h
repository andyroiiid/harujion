//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_SPRITE_VERTICES_H
#define HARUJION_SPRITE_VERTICES_H

#include "non_copyable.h"
#include "renderer/vertex_array.h"

class SpriteVertices {
public:
    static SpriteVertices &getInstance();

    inline void bindAndDraw() { vao.bindAndDraw(GL_TRIANGLE_STRIP); }

private:
    SpriteVertices();

    VertexArray vao;
};

#endif //HARUJION_SPRITE_VERTICES_H
