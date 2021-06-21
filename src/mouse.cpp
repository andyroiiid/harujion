//
// Created by andyroiiid on 6/15/2021.
//

#include "mouse.h"

Mouse &Mouse::getInstance() {
    static Mouse instance;
    return instance;
}

Mouse::Mouse() {
    glfwSetMouseButtonCallback(window.glfwWindow, [](GLFWwindow *_, int button, int action, int mods) {
        auto &mouse = Mouse::getInstance();
        mouse.currState[button] = action;
    });
    glfwSetCursorPosCallback(window.glfwWindow, [](GLFWwindow *_, double xPos, double yPos) {
        auto &mouse = Mouse::getInstance();
        mouse.x = static_cast<float>(xPos);
        mouse.y = static_cast<float>(yPos);
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

std::tuple<float, float> Mouse::normalizedPosition() {
    auto[width, height] = window.getFramebufferSize();
    return std::make_tuple(x / static_cast<float >(width), 1.0f - y / static_cast<float>(height));
}

void Mouse::setCursor(bool enable) {
    glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
