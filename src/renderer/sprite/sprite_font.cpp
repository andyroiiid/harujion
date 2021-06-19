//
// Created by andyroiiid on 6/16/2021.
//

#include "renderer/sprite/sprite_font.h"

SpriteFont::SpriteFont(const std::string &filename, int pixelsPerUnit) {
    texture = Texture::load(filename, false, false, false);
    glm::ivec2 textureSize = texture->size();
    glyphPixelSize = {textureSize.x / 16, textureSize.y / 8};
    scale = 1.0f / static_cast<float>(pixelsPerUnit);
}

void SpriteFont::draw(float x, float y, const std::string &string) {
    if (!texture) return;

    shader.use();
    texture->bind(0);
    shader.setTexturePixelSize(texture->size());
    shader.setPixelPivot({0.0f, 0.0f});
    shader.setRotation(0.0f);
    shader.setScale(scale, scale);
    shader.setFlip(false, false);
    float deltaX = static_cast<float>(glyphPixelSize.x) * scale;
    for (int i = 0; i < string.size(); i++) {
        shader.setPixelRect(getGlyphRect(string[i]));
        shader.setPosition(x + static_cast<float>(i) * deltaX, y);
        vertices.bindAndDraw();
    }
    glBindVertexArray(0);
    glBindTextureUnit(0, 0);
    glUseProgram(0);
}

glm::ivec4 SpriteFont::getGlyphRect(char c) const {
    int column = c % 16;
    int row = 7 - c / 16;
    return glm::ivec4(column * glyphPixelSize.x, row * glyphPixelSize.y, glyphPixelSize.x, glyphPixelSize.y);
}
