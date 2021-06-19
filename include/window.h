//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_WINDOW_H
#define HARUJION_WINDOW_H

#include <GLFW/glfw3.h>
#include <sol/forward.hpp>

#include "non_copyable.h"

class Window : NonCopyable {
public:
    static Window &getInstance();

    bool shouldClose();

    void swapBuffers();

    void getFramebufferSize(int *w, int *h);

    void bindFunctions(sol::table &haru);

    void setTitle(const char *title);

private:
    Window();

    ~Window();

    friend class Keyboard;

    friend class Mouse;

    friend class Renderer;

    GLFWwindow *window = nullptr;
};

#endif //HARUJION_WINDOW_H
