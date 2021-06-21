//
// Created by andyroiiid on 6/19/2021.
//

#include "keyboard.h"

Keyboard &Keyboard::getInstance() {
    static Keyboard instance;
    return instance;
}

Keyboard::Keyboard() {
    glfwSetKeyCallback(window.glfwWindow, [](GLFWwindow *_, int key, int scancode, int action, int mods) {
        auto &keyboard = Keyboard::getInstance();
        keyboard.currState[key] = action;
    });
}

void Keyboard::update() {
    std::copy(currState.begin(), currState.end(), prevState.begin());
}

bool Keyboard::pressed(int key) {
    return currState[key];
}

bool Keyboard::justPressed(int key) {
    return currState[key] && !prevState[key];
}

bool Keyboard::justReleased(int key) {
    return !currState[key] && prevState[key];
}
