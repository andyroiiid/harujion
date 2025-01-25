// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "renderer/shader.h"

class SpriteShader : public Shader
{
public:
    static SpriteShader &getInstance();

    void setTexturePixelSize(const glm::ivec2 &size);

    void setPixelRect(const glm::ivec4 &rect);

    void setPixelPivot(const glm::vec2 &pivot);

    void setFlip(bool flipX, bool flipY);

    void setPosition(float x, float y);

    void setRotation(float r);

    void setScale(float sx, float sy);

private:
    SpriteShader();

    GLint texturePixelSizeLocation = 0;
    GLint pixelRectLocation        = 0;
    GLint pixelPivotLocation       = 0;
    GLint flipLocation             = 0;
    GLint positionLocation         = 0;
    GLint rotationLocation         = 0;
    GLint scaleLocation            = 0;
};
