// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <glad/gl.h>
#include <glm/mat4x4.hpp>

#include "non_copyable.h"

class ShaderGlobals : NonCopyable
{
public:
    static ShaderGlobals &getInstance();

    ShaderGlobals &setMatrix(const glm::mat4 &matrix);

private:
    ShaderGlobals();

    ~ShaderGlobals();

    GLuint dataBuffer = 0;
};
