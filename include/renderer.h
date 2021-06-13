//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_RENDERER_H
#define HARUJION_RENDERER_H

#include "non_copyable.h"
#include "window.h"

class Renderer : NonCopyable {
public:
    static Renderer &getInstance();

    void clear();

    float clearColor[4] = {0.2f, 0.2f, 0.2f, 1.0f};

private:
    Renderer();

    Window &window = Window::getInstance();
};

#endif //HARUJION_RENDERER_H
