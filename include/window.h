//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_WINDOW_H
#define HARUJION_WINDOW_H

#include "non_copyable.h"

struct GLFWwindow;

class Window : NonCopyable {
public:
    static Window &getInstance();

    bool shouldClose();

    void pollEvents();

    void swapBuffers();

private:
    Window();

    ~Window();

    GLFWwindow *window = nullptr;
};

#endif //HARUJION_WINDOW_H
