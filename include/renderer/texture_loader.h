// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "non_copyable.h"
#include "renderer/texture.h"

class TextureLoader : NonCopyable
{
public:
    static TextureLoader &getInstance();

    std::shared_ptr<Texture> load(const std::string &filename, bool filter, bool clamp, bool mipmap);

private:
    std::unordered_map<std::string, std::weak_ptr<Texture>> cache;
};
