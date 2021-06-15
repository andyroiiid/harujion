//
// Created by andyroiiid on 6/15/2021.
//

#ifndef HARUJION_INPUT_H
#define HARUJION_INPUT_H

#include <array>
#include <sol/forward.hpp>

#include "non_copyable.h"
#include "window.h"

class Input : NonCopyable {
public:
    static Input &getInstance();

    void update();

    sol::table getLuaTable(sol::state &lua);

    bool keyPressed(int key);

    bool keyJustPressed(int key);

    bool keyJustReleased(int key);

private:
    Input();

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    Window &window = Window::getInstance();

    std::array<bool, GLFW_KEY_LAST + 1> prevKeyState{false};
    std::array<bool, GLFW_KEY_LAST + 1> currKeyState{false};
};

#endif //HARUJION_INPUT_H
