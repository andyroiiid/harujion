//
// Created by andyroiiid on 6/14/2021.
//

#include "renderer/sprite/sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> &texture, int pixelsPerUnit)
        : texture(texture) {
    glm::ivec2 textureSize = texture->size();
    pixelRect = {0, 0, textureSize.x, textureSize.y};
    pixelPivot = glm::vec2(textureSize) / 2.0f;
    scale = 1.0f / static_cast<float>(pixelsPerUnit);
}

void Sprite::setPixelRect(int x, int y, int w, int h) {
    pixelRect = {x, y, w, h};
}

void Sprite::setPixelPivot(float x, float y) {
    pixelPivot = {x, y};
}

void Sprite::setFlip(bool x, bool y) {
    flipX = x;
    flipY = y;
}

void Sprite::draw(float x, float y, float rotation) {
    if (!texture) return;

    shader.use();
    shader.setTexturePixelSize(texture->size());
    shader.setPixelRect(pixelRect);
    shader.setPixelPivot(pixelPivot);
    shader.setPosition(x, y);
    shader.setRotation(rotation);
    shader.setScale(scale, scale);
    shader.setFlip(flipX, flipY);
    texture->bind(0);
    vertices.bindAndDraw();
    glBindVertexArray(0);
    glBindTextureUnit(0, 0);
    glUseProgram(0);
}
