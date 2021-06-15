//
// Created by andyroiiid on 6/15/2021.
//

#ifndef HARUJION_CAMERA_H
#define HARUJION_CAMERA_H

#include <glm/mat4x4.hpp>

class Camera {
public:
    void framebufferResize(int width, int height);

    void setHalfHeight(float newHalfHeight);

    const glm::mat4 &getMatrix() const;

private:
    float screenRatio = 1.0f;
    float halfHeight = 1.0f;

    mutable bool matrixDirty = true;
    mutable glm::mat4 matrix;
};

#endif //HARUJION_CAMERA_H
