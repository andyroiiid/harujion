// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include "renderer/sprite/sprite_shader.h"
#include "renderer/sprite/sprite_vertices.h"
#include "renderer/texture.h"

class SpriteFont
{
public:
    explicit SpriteFont(const std::string &filename);

    [[nodiscard]]
    std::tuple<int, int> getGlyphPixelSize() const
    {
        return std::make_tuple(glyphPixelSize.x, glyphPixelSize.y);
    }

    void draw(float x, float y, const std::string &text, float s);

private:
    [[nodiscard]] glm::ivec4 getGlyphRect(char c) const;

    SpriteShader   &shader   = SpriteShader::getInstance();
    SpriteVertices &vertices = SpriteVertices::getInstance();

    std::shared_ptr<Texture> texture;
    glm::ivec2               glyphPixelSize {0, 0};
};
