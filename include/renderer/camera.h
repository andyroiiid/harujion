//
// Created by andyroiiid on 6/15/2021.
//

#ifndef HARUJION_CAMERA_H
#define HARUJION_CAMERA_H

#include <sol/forward.hpp>

#include "non_copyable.h"
#include "renderer/shader_globals.h"

class Camera : NonCopyable {
public:
    static Camera &getInstance();

    void framebufferResize(int width, int height);

    void update();

    sol::table getLuaTable(sol::state &lua);

    void setHalfHeight(float newHalfHeight);

    void setCenter(float x, float y);

private:
    Camera() = default;

    ShaderGlobals &shaderGlobals = ShaderGlobals::getInstance();

    float screenRatio = 1.0f;
    float halfHeight = 1.0f;

    glm::vec2 center = {0.0f, 0.0f};

    mutable bool matrixDirty = true;
};

#endif //HARUJION_CAMERA_H
