//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_TEXTURE_H
#define HARUJION_TEXTURE_H

#include <string>
#include <memory>
#include <glad/gl.h>
#include <glm/vec2.hpp>

#include "non_copyable.h"

class Texture : NonCopyable {
public:
    Texture(const std::string &filename, bool filter, bool clamp, bool mipmap);

    ~Texture();

    void bind(GLuint unit);

    [[nodiscard]] inline glm::ivec2 size() const { return _size; }

    static std::shared_ptr<Texture> load(const std::string &filename,
                                         bool filter = false, bool clamp = false, bool mipmap = false);

private:
    glm::ivec2 _size{0, 0,};

    GLuint texture = 0;
};

#endif //HARUJION_TEXTURE_H
