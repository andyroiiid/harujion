//
// Created by andyroiiid on 6/14/2021.
//

#ifndef HARUJION_SHADER_H
#define HARUJION_SHADER_H

#include <string>
#include <glad/gl.h>

#include "non_copyable.h"

class Shader : NonCopyable {
public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);

    ~Shader();

    void use();

protected:
    static GLuint createShader(GLenum type, const char *source);

    static GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint program = 0;
};

#endif //HARUJION_SHADER_H
