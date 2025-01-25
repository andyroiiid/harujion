// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <glm/vec2.hpp>
#include <string>

#include "non_copyable.h"

class Image : NonCopyable
{
public:
    explicit Image(const std::string &filename);

    ~Image();

    [[nodiscard]] inline const glm::ivec2 &size() const { return _size; }

    [[nodiscard]] inline const unsigned char *data() const { return _data; }

private:
    glm::ivec2     _size {0, 0};
    unsigned char *_data = nullptr;
};
