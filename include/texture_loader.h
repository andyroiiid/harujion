//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_TEXTURE_LOADER_H
#define HARUJION_TEXTURE_LOADER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "non_copyable.h"
#include "texture.h"

class TextureLoader : NonCopyable {
public:
    static TextureLoader &getInstance();

    std::shared_ptr<Texture> load(const std::string &filename, bool filter, bool clamp, bool mipmap);

private:
    std::unordered_map<std::string, std::weak_ptr<Texture>> cache;
};

#endif //HARUJION_TEXTURE_LOADER_H
