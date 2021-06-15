//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_SHADER_GLOBALS_H
#define HARUJION_SHADER_GLOBALS_H

#include <glad/gl.h>
#include <glm/mat4x4.hpp>

#include "non_copyable.h"

class ShaderGlobals : NonCopyable {
public:
    static ShaderGlobals &getInstance();

    ShaderGlobals &setMatrix(const glm::mat4 &matrix);

private:
    ShaderGlobals();

    ~ShaderGlobals();

    GLuint dataBuffer = 0;
};

#endif //HARUJION_SHADER_GLOBALS_H
