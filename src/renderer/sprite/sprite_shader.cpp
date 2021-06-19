//
// Created by andyroiiid on 6/14/2021.
//

#include "renderer/sprite/sprite_shader.h"

#include <glm/gtc/type_ptr.hpp>

SpriteShader &SpriteShader::getInstance() {
    static SpriteShader instance;
    return instance;
}

SpriteShader::SpriteShader() : Shader(R"GLSL(
#version 450 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;

layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec4 vColor;

layout(location = 0) uniform ivec2 uTexturePixelSize;
layout(location = 1) uniform ivec4 uPixelRect;
layout(location = 2) uniform vec2 uPixelPivot;
layout(location = 3) uniform bvec2 uFlip;
layout(location = 4) uniform vec2 uPosition;
layout(location = 5) uniform float uRotation;
layout(location = 6) uniform vec2 uScale;

layout(std140, binding = 0) uniform ShaderGlobalData {
    mat4 uMatrix;
};

vec2 flippedTexCoord(vec2 texCoord) {
    return vec2(
        uFlip.x ? 1.0 - texCoord.x : texCoord.x,
        uFlip.y ? 1.0 - texCoord.y : texCoord.y
    );
}

vec2 flippedPixelPivot(ivec2 pixelSize, vec2 pixelPivot) {
    return vec2(
        uFlip.x ? pixelSize.x - pixelPivot.x : pixelPivot.x,
        uFlip.y ? pixelSize.y - pixelPivot.y : pixelPivot.y
    );
}

vec2 rotate(vec2 pos, float angle) {
    return vec2(
        cos(angle) * pos.x - sin(angle) * pos.y,
        sin(angle) * pos.x + cos(angle) * pos.y
    );
}

void main() {
    ivec2 pixelSize = uPixelRect.zw;
    vec2 pixelPos = aPosition * pixelSize - flippedPixelPivot(pixelSize, uPixelPivot);
    vec2 worldPos = uPosition + rotate(uScale * pixelPos, uRotation);
    gl_Position = uMatrix * vec4(worldPos, 0, 1);
    vec2 offset = vec2(uPixelRect.xy) / uTexturePixelSize;
    vec2 size = vec2(pixelSize) / uTexturePixelSize;
    vTexCoord = offset + size * flippedTexCoord(aTexCoord);
    vColor = aColor;
}
)GLSL", R"GLSL(
#version 450 core
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec4 vColor;

layout(location = 0) out vec4 fColor;

layout(binding = 0) uniform sampler2D uTexture;

void main() {
    fColor = texture(uTexture, vTexCoord) * vColor;
}
)GLSL") {
    texturePixelSizeLocation = glGetUniformLocation(program, "uTexturePixelSize");
    pixelRectLocation = glGetUniformLocation(program, "uPixelRect");
    pixelPivotLocation = glGetUniformLocation(program, "uPixelPivot");
    flipLocation = glGetUniformLocation(program, "uFlip");
    positionLocation = glGetUniformLocation(program, "uPosition");
    rotationLocation = glGetUniformLocation(program, "uRotation");
    scaleLocation = glGetUniformLocation(program, "uScale");
}

void SpriteShader::setTexturePixelSize(const glm::ivec2 &size) {
    glProgramUniform2iv(program, texturePixelSizeLocation, 1, glm::value_ptr(size));
}

void SpriteShader::setPixelRect(const glm::ivec4 &rect) {
    glProgramUniform4iv(program, pixelRectLocation, 1, glm::value_ptr(rect));
}

void SpriteShader::setPixelPivot(const glm::vec2 &pivot) {
    glProgramUniform2fv(program, pixelPivotLocation, 1, glm::value_ptr(pivot));
}

void SpriteShader::setFlip(bool flipX, bool flipY) {
    glProgramUniform2i(program, flipLocation, flipX, flipY);
}

void SpriteShader::setPosition(float x, float y) {
    glProgramUniform2f(program, positionLocation, x, y);
}

void SpriteShader::setRotation(float r) {
    glProgramUniform1f(program, rotationLocation, r);
}

void SpriteShader::setScale(float sx, float sy) {
    glProgramUniform2f(program, scaleLocation, sx, sy);
}
