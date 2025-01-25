// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#pragma once

#include <GLFW/glfw3.h>
#include <tuple>

#include "non_copyable.h"

class Window : NonCopyable
{
public:
    static Window &getInstance();

    bool shouldClose();

    void swapBuffers();

    void close();

    std::tuple<int, int> getFramebufferSize();

    void setTitle(const char *title);

private:
    Window();

    ~Window();

    friend class Keyboard;

    friend class Mouse;

    GLFWwindow *glfwWindow = nullptr;
};
