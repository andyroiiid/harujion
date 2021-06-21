//
// Created by andyroiiid on 6/16/2021.
//

#ifndef HARUJION_SPRITE_FONT_H
#define HARUJION_SPRITE_FONT_H

#include "non_copyable.h"
#include "renderer/sprite/sprite_shader.h"
#include "renderer/sprite/sprite_vertices.h"
#include "renderer/texture.h"

class SpriteFont {
public:
    explicit SpriteFont(const std::string &filename);

    void draw(float x, float y, const std::string &text, float s);

private:
    [[nodiscard]] glm::ivec4 getGlyphRect(char c) const;

    SpriteShader &shader = SpriteShader::getInstance();
    SpriteVertices &vertices = SpriteVertices::getInstance();

    std::shared_ptr<Texture> texture;
    glm::ivec2 glyphPixelSize{0, 0};
};

#endif //HARUJION_SPRITE_FONT_H
