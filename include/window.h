//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_WINDOW_H
#define HARUJION_WINDOW_H

#include <sol/forward.hpp>

#include "non_copyable.h"

struct GLFWwindow;

class Window : NonCopyable {
public:
    static Window &getInstance();

    bool shouldClose();

    void swapBuffers();

    void getFramebufferSize(int *w, int *h);

    sol::table getLuaTable(sol::state &lua);

    void setTitle(const char *title);

    bool isKeyPressed(int key);

private:
    Window();

    ~Window();

    GLFWwindow *window = nullptr;
};

#endif //HARUJION_WINDOW_H
