// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include "renderer/shader.h"

class DynamicDrawShader : public Shader
{
public:
    static DynamicDrawShader &getInstance();

private:
    DynamicDrawShader();
};
