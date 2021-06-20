//
// Created by andyroiiid on 6/15/2021.
//

#ifndef HARUJION_MOUSE_H
#define HARUJION_MOUSE_H

#include <array>

#include "non_copyable.h"
#include "window.h"
#include "renderer/camera.h"

class Mouse : NonCopyable {
public:
    static Mouse &getInstance();

    void update();

    bool pressed(int button);

    bool justPressed(int button);

    bool justReleased(int button);

    std::tuple<float, float> canvasPosition();

    std::tuple<float, float> worldPosition();

    void setCursor(bool enable);

private:
    Mouse();

    Window &window = Window::getInstance();
    Camera &camera = Camera::getInstance();

    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> prevState{false};
    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> currState{false};

    int x = 0;
    int y = 0;
};

#endif //HARUJION_MOUSE_H
