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

sol::table Input::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table.set_function("keyPressed", [this](int key) { return keyPressed(key); });
    table.set_function("keyJustPressed", [this](int key) { return keyJustPressed(key); });
    table.set_function("keyJustReleased", [this](int key) { return keyJustReleased(key); });
    table.set_function("mouseButtonPressed", [this](int button) { return mouseButtonPressed(button); });
    table.set_function("mouseButtonJustPressed", [this](int button) { return mouseButtonJustPressed(button); });
    table.set_function("mouseButtonJustReleased", [this](int button) { return mouseButtonJustReleased(button); });
    table.set_function("mousePosition", [this]() { return mousePosition(); });
    table.set_function("mouseWorldPosition", [this]() { return mouseWorldPosition(); });
    return table;
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
