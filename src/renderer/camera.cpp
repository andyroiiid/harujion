//
// Created by andyroiiid on 6/15/2021.
//

#include "renderer/camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <sol/sol.hpp>

Camera &Camera::getInstance() {
    static Camera instance;
    return instance;
}

void Camera::framebufferResize(int width, int height) {
    screenWidth = static_cast<float>(width);
    screenHeight = static_cast<float>(height);
    matrixDirty = true;
}

void Camera::update() {
    if (matrixDirty) {
        halfWidth = screenWidth / screenHeight * halfHeight;
        shaderGlobals.setMatrix(glm::ortho(
                center.x - halfWidth,
                center.x + halfWidth,
                center.y - halfHeight,
                center.y + halfHeight
        ));
        matrixDirty = false;
    }
}

sol::table Camera::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table.set_function(
            "setHalfHeight",
            [this](float newHalfHeight) { setHalfHeight(newHalfHeight); }
    );
    table.set_function(
            "setCenter",
            [this](float x, float y) { setCenter(x, y); }
    );
    table.set_function(
            "screenToWorld",
            [this](int x, int y) { return screenToWorld(x, y); }
    );
    return table;
}

void Camera::setHalfHeight(float newHalfHeight) {
    halfHeight = newHalfHeight;
    matrixDirty = true;
}

void Camera::setCenter(float x, float y) {
    center = {x, y};
    matrixDirty = true;
}

std::tuple<float, float> Camera::screenToWorld(int x, int y) const {
    float normalizedX = static_cast<float>(x) / screenWidth * 2.0f - 1.0f;
    float normalizedY = 1.0f - static_cast<float>(y) / screenHeight * 2.0f;
    return std::make_tuple(
            center.x + normalizedX * halfWidth,
            center.y + normalizedY * halfHeight
    );
}
