//
// Created by andyroiiid on 6/15/2021.
//

#include "input.h"

#include <sol/sol.hpp>

Input &Input::getInstance() {
    static Input instance;
    return instance;
}

Input::Input() {
    glfwSetKeyCallback(window.window, [](GLFWwindow *_, int key, int scancode, int action, int mods) {
        auto &input = Input::getInstance();
        input.currKeyState[key] = action;
    });
    glfwSetMouseButtonCallback(window.window, [](GLFWwindow *_, int button, int action, int mods) {
        auto &input = Input::getInstance();
        input.currMouseButtonState[button] = action;
    });
    glfwSetCursorPosCallback(window.window, [](GLFWwindow *_, double xPos, double yPos) {
        auto &input = Input::getInstance();
        input.mouseX = static_cast<int>(xPos);
        input.mouseY = static_cast<int>(yPos);
    });
}

void Input::update() {
    std::copy(currKeyState.begin(), currKeyState.end(), prevKeyState.begin());
    std::copy(currMouseButtonState.begin(), currMouseButtonState.end(), prevMouseButtonState.begin());
}

void Input::bindFunctions(sol::table &haru) {
    haru.create_named(
            "input",
            "keyPressed", [this](int key) { return keyPressed(key); },
            "keyJustPressed", [this](int key) { return keyJustPressed(key); },
            "keyJustReleased", [this](int key) { return keyJustReleased(key); },
            "mouseButtonPressed", [this](int button) { return mouseButtonPressed(button); },
            "mouseButtonJustPressed", [this](int button) { return mouseButtonJustPressed(button); },
            "mouseButtonJustReleased", [this](int button) { return mouseButtonJustReleased(button); },
            "mousePosition", [this]() { return mousePosition(); },
            "mouseWorldPosition", [this]() { return mouseWorldPosition(); },
            "setCursor", [this](bool enable) { return setCursor(enable); }
    );
}

bool Input::keyPressed(int key) {
    return currKeyState[key];
}

bool Input::keyJustPressed(int key) {
    return currKeyState[key] && !prevKeyState[key];
}

bool Input::keyJustReleased(int key) {
    return !currKeyState[key] && prevKeyState[key];
}

bool Input::mouseButtonPressed(int button) {
    return currMouseButtonState[button];
}

bool Input::mouseButtonJustPressed(int button) {
    return currMouseButtonState[button] && !prevMouseButtonState[button];
}

bool Input::mouseButtonJustReleased(int button) {
    return !currMouseButtonState[button] && prevMouseButtonState[button];
}

std::tuple<int, int> Input::mousePosition() {
    return std::make_tuple(mouseX, mouseY);
}

std::tuple<float, float> Input::mouseWorldPosition() {
    return camera.screenToWorld(mouseX, mouseY);
}

void Input::setCursor(bool enable) {
    glfwSetInputMode(window.window, GLFW_CURSOR, enable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}
