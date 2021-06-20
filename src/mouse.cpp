//
// Created by andyroiiid on 6/15/2021.
//

#include "mouse.h"

Mouse &Mouse::getInstance() {
    static Mouse instance;
    return instance;
}

Mouse::Mouse() {
    glfwSetMouseButtonCallback(window.window, [](GLFWwindow *_, int button, int action, int mods) {
        auto &mouse = Mouse::getInstance();
        mouse.currState[button] = action;
    });
    glfwSetCursorPosCallback(window.window, [](GLFWwindow *_, double xPos, double yPos) {
        auto &mouse = Mouse::getInstance();
        mouse.x = static_cast<int>(xPos);
        mouse.y = static_cast<int>(yPos);
    });
}

void Mouse::update() {
    std::copy(currState.begin(), currState.end(), prevState.begin());
}

bool Mouse::pressed(int button) {
    return currState[button];
}

bool Mouse::justPressed(int button) {
    return currState[button] && !prevState[button];
}

bool Mouse::justReleased(int button) {
    return !currState[button] && prevState[button];
}

std::tuple<float, float> Mouse::canvasPosition() {
    return camera.screenToCanvas(x, y);
}

std::tuple<float, float> Mouse::worldPosition() {
    return camera.screenToWorld(x, y);
}

void Mouse::setCursor(bool enable) {
    glfwSetInputMode(window.window, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
