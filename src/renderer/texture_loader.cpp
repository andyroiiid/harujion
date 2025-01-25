// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/texture_loader.h"

#include <spdlog/spdlog.h>

TextureLoader &TextureLoader::getInstance()
{
    static TextureLoader instance;
    return instance;
}

std::shared_ptr<Texture> TextureLoader::load(const std::string &filename, bool filter, bool clamp, bool mipmap)
{
    const auto &pair = cache.find(filename);
    if (pair != cache.end())
    {
        auto &texture = pair->second;
        if (!texture.expired())
        {
            return texture.lock();
        }
        spdlog::info("texture {} expired, reloading", filename);
    }
    else
    {
        spdlog::info("loading texture {}", filename);
    }

    auto texture = std::make_shared<Texture>(filename, filter, clamp, mipmap);
    cache.insert_or_assign(filename, texture);
    return texture;
}
