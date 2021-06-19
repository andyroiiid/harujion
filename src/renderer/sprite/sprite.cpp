//
// Created by andyroiiid on 6/14/2021.
//

#include "renderer/sprite/sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> &texture, int pixelsPerUnit)
        : texture(texture),
          pixelsPerUnit(pixelsPerUnit) {
    glm::ivec2 textureSize = texture->size();
    pixelRect = {0, 0, textureSize.x, textureSize.y};
    pixelPivot = glm::vec2(textureSize) / 2.0f;
}

Sprite::Sprite(const std::string &filename, int pixelsPerUnit)
        : pixelsPerUnit(pixelsPerUnit) {
    texture = Texture::load(filename, false, false, false);
    glm::ivec2 textureSize = texture->size();
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

void Sprite::draw(float x, float y, float rotation) {
    if (!texture) return;

    shader.use();
    shader.setTexturePixelSize(texture->size());
    shader.setPixelRect(pixelRect);
    shader.setPixelPivot(pixelPivot);
    shader.setPixelsPerUnit(pixelsPerUnit);
    shader.setPosition(x, y);
    shader.setRotation(rotation);
    shader.setFlip(flipX, flipY);
    texture->bind(0);
    vertices.bindAndDraw();
    glBindVertexArray(0);
    glBindTextureUnit(0, 0);
    glUseProgram(0);
}
