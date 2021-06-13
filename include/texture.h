//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_TEXTURE_H
#define HARUJION_TEXTURE_H

#include <string>
#include <glad/gl.h>
#include <glm/vec2.hpp>

#include "non_copyable.h"

class Texture : NonCopyable {
public:
    Texture() = default;

    ~Texture();

    void loadFromFile(const std::string &filename, bool filter = false, bool clamp = false, bool mipmap = false);

    void bind(GLuint unit);

    [[nodiscard]] inline glm::ivec2 size() const { return _size; }

private:
    void release();

    glm::ivec2 _size{0, 0,};

    GLuint texture = 0;
};

#endif //HARUJION_TEXTURE_H
