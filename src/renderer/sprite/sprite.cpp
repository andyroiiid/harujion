//
// Created by andyroiiid on 6/14/2021.
//

#include "renderer/sprite/sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> &texture) : texture(texture) {
    const glm::ivec2 &textureSize = texture->size();
    pixelRect = {0, 0, textureSize.x, textureSize.y};
    pixelPivot = glm::vec2(textureSize) / 2.0f;
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

void Sprite::draw(float x, float y, float r, float sx, float sy) {
    if (!texture) return;

    shader.use();
    shader.setTexturePixelSize(texture->size());
    shader.setPixelRect(pixelRect);
    shader.setPixelPivot(pixelPivot);
    shader.setFlip(flipX, flipY);
    shader.setPosition(x, y);
    shader.setRotation(r);
    shader.setScale(sx, sy);
    texture->bind(0);
    vertices.bindAndDraw();
    glBindVertexArray(0);
    glBindTextureUnit(0, 0);
    glUseProgram(0);
}
