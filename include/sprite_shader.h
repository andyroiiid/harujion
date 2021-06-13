//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_SPRITE_SHADER_H
#define HARUJION_SPRITE_SHADER_H

#include "shader.h"

class SpriteShader : public Shader {
public:
    static SpriteShader &getInstance();

private:
    SpriteShader();
};

#endif //HARUJION_SPRITE_SHADER_H
