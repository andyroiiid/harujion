//
// Created by andyroiiid on 6/19/2021.
//

#ifndef HARUJION_KEYBOARD_H
#define HARUJION_KEYBOARD_H

#include <array>

#include "non_copyable.h"
#include "window.h"

class Keyboard : NonCopyable {
public:
    static Keyboard &getInstance();

    void update();

    bool pressed(int key);

    bool justPressed(int key);

    bool justReleased(int key);

private:
    Keyboard();

    Window &window = Window::getInstance();

    std::array<bool, GLFW_KEY_LAST + 1> prevState{false};
    std::array<bool, GLFW_KEY_LAST + 1> currState{false};
};

#endif //HARUJION_KEYBOARD_H
