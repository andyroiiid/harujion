//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_SPRITE_H
#define HARUJION_SPRITE_H

#include "non_copyable.h"
#include "renderer/sprite/sprite_shader.h"
#include "renderer/sprite/sprite_vertices.h"
#include "renderer/texture.h"

class Sprite : NonCopyable {
public:
    Sprite(std::shared_ptr<Texture> &texture, int pixelsPerUnit);

    void setPixelRect(int x, int y, int w, int h);

    void setPixelPivot(float x, float y);

    void setFlip(bool x, bool y);

    void draw(float x, float y, float r);

private:
    SpriteShader &shader = SpriteShader::getInstance();
    SpriteVertices &vertices = SpriteVertices::getInstance();

    std::shared_ptr<Texture> texture;
    glm::ivec4 pixelRect{0, 0, 0, 0};
    glm::vec2 pixelPivot{0, 0};
    bool flipX = false;
    bool flipY = false;
    float scale = 1.0f;
};

#endif //HARUJION_SPRITE_H
