//
// Created by andyroiiid on 6/14/2021.
//

#include "sprite.h"

Sprite::Sprite() {
    texture = Texture::load("test.png", true);
    pixelRect = {0, 0, 600, 600};
    pixelPivot = {300, 300};
    pixelsPerUnit = 600;
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
