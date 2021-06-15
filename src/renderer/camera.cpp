//
// Created by andyroiiid on 6/15/2021.
//

#include "renderer/camera.h"

#include <glm/ext/matrix_clip_space.hpp>

void Camera::framebufferResize(int width, int height) {
    screenRatio = static_cast<float>(width) / static_cast<float>(height);
    matrixDirty = true;
}

void Camera::setHalfHeight(float newHalfHeight) {
    halfHeight = newHalfHeight;
    matrixDirty = true;
}

const glm::mat4 &Camera::getMatrix() const {
    if (matrixDirty) {
        float halfWidth = screenRatio * halfHeight;
        matrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
        matrixDirty = false;
    }
    return matrix;
}
