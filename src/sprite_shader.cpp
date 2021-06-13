//
// Created by andyroiiid on 6/14/2021.
//

#include "sprite_shader.h"

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

void main() {
    gl_Position = vec4(aPosition, 0, 1);
    vTexCoord = aTexCoord;
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
}
