//
// Created by andyroiiid on 6/14/2021.
//

#include "renderer/shader_globals.h"

#include <glm/gtc/type_ptr.hpp>

struct ShaderGlobalData {
    glm::mat4 uMatrix;
};

ShaderGlobals &ShaderGlobals::getInstance() {
    static ShaderGlobals instance;
    return instance;
}

ShaderGlobals::ShaderGlobals() {
    glCreateBuffers(1, &dataBuffer);
    glNamedBufferData(dataBuffer, sizeof(ShaderGlobalData), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, dataBuffer);
}

ShaderGlobals::~ShaderGlobals() {
    glDeleteBuffers(1, &dataBuffer);
}

ShaderGlobals &ShaderGlobals::setMatrix(const glm::mat4 &matrix) {
    glNamedBufferSubData(
            dataBuffer,
            offsetof(ShaderGlobalData, uMatrix),
            sizeof(ShaderGlobalData::uMatrix),
            glm::value_ptr(matrix)
    );
    return *this;
}