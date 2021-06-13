//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_BASIC_SHADER_H
#define HARUJION_BASIC_SHADER_H

#include "shader.h"

class BasicShader : public Shader {
public:
    static BasicShader &getInstance();

private:
    BasicShader();
};

#endif //HARUJION_BASIC_SHADER_H
