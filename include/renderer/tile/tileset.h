//
// Created by andyroiiid on 6/25/2021.
//

#ifndef HARUJION_TILESET_H
#define HARUJION_TILESET_H

#include <vector>

#include "non_copyable.h"
#include "renderer/sprite/sprite_shader.h"
#include "renderer/sprite/sprite_vertices.h"
#include "renderer/texture.h"

class Tileset : NonCopyable {
public:
    Tileset(std::shared_ptr<Texture> &texture, int tileWidth, int tileHeight, int spacing);

    [[nodiscard]] std::tuple<int, int> getTileSize() const { return std::make_tuple(tileWidth, tileHeight); }

    void draw(int idx, float x, float y);

private:
    SpriteShader &shader = SpriteShader::getInstance();
    SpriteVertices &vertices = SpriteVertices::getInstance();

    std::shared_ptr<Texture> texture;
    int tileWidth = 0;
    int tileHeight = 0;
    std::vector<glm::ivec4> tiles;
};

#endif //HARUJION_TILESET_H
