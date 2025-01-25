// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>

#include "non_copyable.h"

class Texture : NonCopyable
{
public:
    Texture(const std::string &filename, bool filter, bool clamp, bool mipmap);

    ~Texture();

    void bind(GLuint unit);

    [[nodiscard]] const glm::ivec2 &size() const { return _size; }

    static std::shared_ptr<Texture> load(const std::string &filename, bool filter, bool clamp, bool mipmap);

private:
    glm::ivec2 _size {
        0,
        0,
    };

    GLuint texture = 0;
};
