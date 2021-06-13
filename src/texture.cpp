//
// Created by andyroiiid on 6/14/2021.
//

#include "texture.h"

#include "image.h"

Texture::~Texture() {
    release();
}

void Texture::loadFromFile(const std::string &filename, bool filter, bool clamp, bool mipmap) {
    release();

    Image image(filename);

    _size = image.size();

    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
    glTextureStorage2D(texture, 1, GL_RGBA8, _size.x, _size.y);
    glTextureSubImage2D(texture, 0, 0, 0, _size.x, _size.y, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

    if (filter) {
        if (mipmap) {
            glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        } else {
            glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    } else {
        glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    if (clamp) {
        glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } else {
        glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    if (mipmap) {
        glGenerateTextureMipmap(texture);
    }
}

void Texture::bind(GLuint unit) { // NOLINT(readability-make-member-function-const)
    glBindTextureUnit(unit, texture);
}

void Texture::release() {
    glDeleteTextures(1, &texture);
}
