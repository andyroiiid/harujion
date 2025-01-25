// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <glad/gl.h>
#include <string>

#include "non_copyable.h"

class Shader : NonCopyable
{
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);

    ~Shader();

    void use();

protected:
    static GLuint createShader(GLenum type, const char *source);

    static GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint program = 0;
};
