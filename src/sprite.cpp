//
// Created by andyroiiid on 6/14/2021.
//

#include "sprite.h"

Sprite::Sprite(const std::string &filename, int pixelsPerUnit) : pixelsPerUnit(pixelsPerUnit) {
    texture = Texture::load(filename);
    glm::ivec2 textureSize = texture->size();
    pixelRect = {0, 0, textureSize.x, textureSize.y};
    pixelPivot = textureSize / 2;
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
