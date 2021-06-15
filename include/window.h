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

    sol::table getLuaTable(sol::state &lua);

    void setTitle(const char *title);

private:
    Window();

    ~Window();

    friend class Input;

    friend class Renderer;

    GLFWwindow *window = nullptr;
};

#endif //HARUJION_WINDOW_H
