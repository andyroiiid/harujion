// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/image.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include "physfs.h"

Image::Image(const std::string &filename)
{
    auto bytes = Physfs::getInstance().readFile(filename);

    _data = stbi_load_from_memory(
        reinterpret_cast<const stbi_uc *>(bytes.data()), //
        static_cast<int>(bytes.length()),
        &_size.x,
        &_size.y,
        nullptr,
        4
    );
}

Image::~Image()
{
    stbi_image_free(_data);
}
