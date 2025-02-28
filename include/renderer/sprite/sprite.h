// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include "non_copyable.h"
#include "renderer/sprite/sprite_shader.h"
#include "renderer/sprite/sprite_vertices.h"
#include "renderer/texture.h"

class Sprite : NonCopyable
{
public:
    explicit Sprite(std::shared_ptr<Texture> &texture);

    void setPixelRect(int x, int y, int w, int h);

    void setPixelPivot(float x, float y);

    void setFlip(bool x, bool y);

    void draw(float x, float y, float r, float sx, float sy);

private:
    SpriteShader   &shader   = SpriteShader::getInstance();
    SpriteVertices &vertices = SpriteVertices::getInstance();

    std::shared_ptr<Texture> texture;
    glm::ivec4               pixelRect {0, 0, 0, 0};
    glm::vec2                pixelPivot {0, 0};
    bool                     flipX = false;
    bool                     flipY = false;
};
