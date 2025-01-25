// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <array>

#include "non_copyable.h"
#include "window.h"

class Mouse : NonCopyable
{
public:
    static Mouse &getInstance();

    void update();

    bool pressed(int button);

    bool justPressed(int button);

    bool justReleased(int button);

    std::tuple<float, float> normalizedPosition();

    void setCursor(bool enable);

private:
    Mouse();

    Window &window = Window::getInstance();

    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> prevState {false};
    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> currState {false};

    float x = 0;
    float y = 0;
};
