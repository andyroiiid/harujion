// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include "renderer/vertex_array.h"

class SpriteVertices
{
public:
    static SpriteVertices &getInstance();

    void bindAndDraw() { vao.bindAndDraw(GL_TRIANGLE_STRIP); }

private:
    SpriteVertices();

    VertexArray vao;
};
