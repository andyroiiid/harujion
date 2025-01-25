// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "renderer/dynamic_draw_shader.h"

DynamicDrawShader &DynamicDrawShader::getInstance()
{
    static DynamicDrawShader instance;
    return instance;
}

DynamicDrawShader::DynamicDrawShader()
    : Shader(
          R"GLSL(
#version 450 core
layout(location = 0) in vec2 aPosition;
layout(location = 2) in vec4 aColor;

layout(location = 0) out vec4 vColor;

layout(std140, binding = 0) uniform ShaderGlobalData {
    mat4 uMatrix;
};

void main() {
    gl_Position = uMatrix * vec4(aPosition, 0, 1);
    vColor = aColor;
}
)GLSL",
          R"GLSL(
#version 450 core
layout(location = 0) in vec4 vColor;

layout(location = 0) out vec4 fColor;

void main() {
    fColor = vColor;
}
)GLSL"
      )
{
}
