//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_DYNAMIC_DRAW_SHADER_H
#define HARUJION_DYNAMIC_DRAW_SHADER_H

#include "shader.h"

class DynamicDrawShader : public Shader {
public:
    static DynamicDrawShader &getInstance();

private:
    DynamicDrawShader();
};

#endif //HARUJION_DYNAMIC_DRAW_SHADER_H
