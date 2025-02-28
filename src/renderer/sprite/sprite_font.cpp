// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/sprite/sprite_font.h"

SpriteFont::SpriteFont(const std::string &filename)
{
    texture                = Texture::load(filename, false, false, false);
    glm::ivec2 textureSize = texture->size();
    glyphPixelSize         = {textureSize.x / 16, textureSize.y / 8};
}

void SpriteFont::draw(float x, float y, const std::string &text, float s)
{
    if (!texture)
    {
        return;
    }

    shader.use();
    texture->bind(0);
    shader.setTexturePixelSize(texture->size());
    shader.setPixelPivot({0.0f, 0.0f});
    shader.setFlip(false, false);
    shader.setRotation(0.0f);
    shader.setScale(s, s);
    auto deltaX = static_cast<float>(glyphPixelSize.x) * s;
    for (int i = 0; i < text.size(); i++)
    {
        shader.setPixelRect(getGlyphRect(text[i]));
        shader.setPosition(x + static_cast<float>(i) * deltaX, y);
        vertices.bindAndDraw();
    }
    glBindVertexArray(0);
    glBindTextureUnit(0, 0);
    glUseProgram(0);
}

glm::ivec4 SpriteFont::getGlyphRect(char c) const
{
    int column = c % 16;
    int row    = 7 - c / 16;
    return {column * glyphPixelSize.x, row * glyphPixelSize.y, glyphPixelSize.x, glyphPixelSize.y};
}
