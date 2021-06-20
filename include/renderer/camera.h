//
// Created by andyroiiid on 6/15/2021.
//

#ifndef HARUJION_CAMERA_H
#define HARUJION_CAMERA_H

#include <tuple>

#include "non_copyable.h"
#include "renderer/shader_globals.h"

class Camera : NonCopyable {
public:
    static Camera &getInstance();

    void framebufferResize(int width, int height);

    void update();

    std::tuple<float, float> screenToCanvas(int x, int y) const;

    std::tuple<float, float> screenToWorld(int x, int y) const;

    void setHalfHeight(float newHalfHeight);

    void setCenter(float x, float y);

private:
    Camera() = default;

    ShaderGlobals &shaderGlobals = ShaderGlobals::getInstance();

    float screenWidth = 1.0f;
    float screenHeight = 1.0f;

    float halfWidth = 1.0f;
    float halfHeight = 1.0f;

    glm::vec2 center = {0.0f, 0.0f};

    mutable bool matrixDirty = true;
};

#endif //HARUJION_CAMERA_H
