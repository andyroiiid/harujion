//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_SPRITE_SHADER_H
#define HARUJION_SPRITE_SHADER_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "renderer/shader.h"

class SpriteShader : public Shader {
public:
    static SpriteShader &getInstance();

    void setTexturePixelSize(const glm::ivec2 &size);

    void setPixelRect(const glm::ivec4 &rect);

    void setPixelPivot(const glm::vec2 &pivot);

    void setPosition(float x, float y);

    void setRotation(float r);

    void setScale(float sx, float sy);

    void setFlip(bool flipX, bool flipY);

private:
    SpriteShader();

    GLint texturePixelSizeLocation = 0;
    GLint pixelRectLocation = 0;
    GLint pixelPivotLocation = 0;
    GLint positionLocation = 0;
    GLint rotationLocation = 0;
    GLint scaleLocation = 0;
    GLint flipLocation = 0;
};

#endif //HARUJION_SPRITE_SHADER_H
