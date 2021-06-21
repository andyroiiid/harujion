//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_WINDOW_H
#define HARUJION_WINDOW_H

#include <tuple>
#include <GLFW/glfw3.h>

#include "non_copyable.h"

class Window : NonCopyable {
public:
    static Window &getInstance();

    bool shouldClose();

    void swapBuffers();

    std::tuple<int, int> getFramebufferSize();

    void setTitle(const char *title);

private:
    Window();

    ~Window();

    friend class Keyboard;

    friend class Mouse;

    GLFWwindow *glfwWindow = nullptr;
};

#endif //HARUJION_WINDOW_H
