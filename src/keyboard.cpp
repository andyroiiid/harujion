//
// Created by andyroiiid on 6/19/2021.
//

#include "keyboard.h"

#include <sol/sol.hpp>

Keyboard &Keyboard::getInstance() {
    static Keyboard instance;
    return instance;
}

Keyboard::Keyboard() {
    glfwSetKeyCallback(window.window, [](GLFWwindow *_, int key, int scancode, int action, int mods) {
        auto &keyboard = Keyboard::getInstance();
        keyboard.currState[key] = action;
    });
}

void Keyboard::update() {
    std::copy(currState.begin(), currState.end(), prevState.begin());
}

void Keyboard::bindFunctions(sol::table &haru) {
    haru.create_named(
            "keyboard",
            "pressed", [this](int key) { return pressed(key); },
            "justPressed", [this](int key) { return justPressed(key); },
            "justReleased", [this](int key) { return justReleased(key); }
    );
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
