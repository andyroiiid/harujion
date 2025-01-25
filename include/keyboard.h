// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <array>

#include "non_copyable.h"
#include "window.h"

class Keyboard : NonCopyable
{
public:
    static Keyboard &getInstance();

    void update();

    bool pressed(int key);

    bool justPressed(int key);

    bool justReleased(int key);

private:
    Keyboard();

    Window &window = Window::getInstance();

    std::array<bool, GLFW_KEY_LAST + 1> prevState {false};
    std::array<bool, GLFW_KEY_LAST + 1> currState {false};
};
