//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_IMAGE_H
#define HARUJION_IMAGE_H

#include <string>
#include <glm/vec2.hpp>

#include "non_copyable.h"

class Image : NonCopyable {
public:
    explicit Image(const std::string &filename);

    ~Image();

    [[nodiscard]] inline glm::ivec2 size() const { return _size; }

    [[nodiscard]] inline const unsigned char *data() const { return _data; }

private:
    glm::ivec2 _size{0, 0};
    unsigned char *_data = nullptr;
};

#endif //HARUJION_IMAGE_H
