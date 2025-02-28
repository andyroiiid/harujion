// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/sprite/sprite_vertices.h"

SpriteVertices &SpriteVertices::getInstance()
{
    static SpriteVertices instance;
    return instance;
}

SpriteVertices::SpriteVertices()
{
    vao.setData(
        {
            {glm::vec2 {0.0f, 0.0f}, glm::vec2 {0.0f, 0.0f}, glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f}},
            {glm::vec2 {1.0f, 0.0f}, glm::vec2 {1.0f, 0.0f}, glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f}},
            {glm::vec2 {0.0f, 1.0f}, glm::vec2 {0.0f, 1.0f}, glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f}},
            {glm::vec2 {1.0f, 1.0f}, glm::vec2 {1.0f, 1.0f}, glm::vec4 {1.0f, 1.0f, 1.0f, 1.0f}}
    },
        GL_STATIC_DRAW
    );
}
