//
// Created by andyroiiid on 6/25/2021.
//

#include "renderer/tile/tileset.h"

Tileset::Tileset(std::shared_ptr<Texture> &texture, int tileWidth, int tileHeight, int spacing)
        : texture(texture), tileWidth(tileWidth), tileHeight(tileHeight) {
    const glm::ivec2 &textureSize = texture->size();
    int columns = (textureSize.x + spacing) / (tileWidth + spacing);
    int rows = (textureSize.y + spacing) / (tileHeight + spacing);
    for (int y = rows - 1; y >= 0; y--) {
        for (int x = 0; x < columns; x++) {
            tiles.emplace_back(x * (tileWidth + spacing), y * (tileHeight + spacing), tileWidth, tileHeight);
        }
    }
}

void Tileset::draw(int idx, float x, float y) {
    if (idx <= 0 || idx > tiles.size() || !texture) return;;

    shader.use();
    shader.setTexturePixelSize(texture->size());
    shader.setPixelRect(tiles[idx - 1]);
    shader.setPixelPivot({0, 0});
    shader.setFlip(false, false);
    shader.setPosition(x, y);
    shader.setRotation(0);
    shader.setScale(1.0001, 1.0001);
    texture->bind(0);
    vertices.bindAndDraw();
    glBindVertexArray(0);
    glBindTextureUnit(0, 0);
    glUseProgram(0);
}
