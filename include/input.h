//
// Created by andyroiiid on 6/15/2021.
//

#ifndef HARUJION_INPUT_H
#define HARUJION_INPUT_H

#include <array>
#include <sol/forward.hpp>

#include "non_copyable.h"
#include "window.h"
#include "renderer/camera.h"

class Input : NonCopyable {
public:
    static Input &getInstance();

    void update();

    sol::table getLuaTable(sol::state &lua);

    bool keyPressed(int key);

    bool keyJustPressed(int key);

    bool keyJustReleased(int key);

    bool mouseButtonPressed(int button);

    bool mouseButtonJustPressed(int button);

    bool mouseButtonJustReleased(int button);

    std::tuple<int, int> mousePosition();

    std::tuple<float, float> mouseWorldPosition();

private:
    Input();

    Window &window = Window::getInstance();
    Camera &camera = Camera::getInstance();

    std::array<bool, GLFW_KEY_LAST + 1> prevKeyState{false};
    std::array<bool, GLFW_KEY_LAST + 1> currKeyState{false};

    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> prevMouseButtonState{false};
    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> currMouseButtonState{false};

    int mouseX = 0;
    int mouseY = 0;
};

#endif //HARUJION_INPUT_H
