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
    glfwSetKeyCallback(window.window, keyCallback);
    glfwSetMouseButtonCallback(window.window, mouseButtonCallback);
}

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto &input = Input::getInstance();
    input.currKeyState[key] = action;
}

void Input::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    auto &input = Input::getInstance();
    input.currMouseButtonState[button] = action;
}

void Input::update() {
    std::copy(currKeyState.begin(), currKeyState.end(), prevKeyState.begin());
    std::copy(currMouseButtonState.begin(), currMouseButtonState.end(), prevMouseButtonState.begin());
    glfwPollEvents();
}

sol::table Input::getLuaTable(sol::state &lua) {
    sol::table table = lua.create_table();
    table.set_function("keyPressed", [this](int key) { return keyPressed(key); });
    table.set_function("keyJustPressed", [this](int key) { return keyJustPressed(key); });
    table.set_function("keyJustReleased", [this](int key) { return keyJustReleased(key); });
    table.set_function("mouseButtonPressed", [this](int button) { return mouseButtonPressed(button); });
    table.set_function("mouseButtonJustPressed", [this](int button) { return mouseButtonJustPressed(button); });
    table.set_function("mouseButtonJustReleased", [this](int button) { return mouseButtonJustReleased(button); });
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
