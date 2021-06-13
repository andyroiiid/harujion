//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_RENDERER_H
#define HARUJION_RENDERER_H

#include <sol/forward.hpp>

#include "non_copyable.h"
#include "window.h"
#include "basic_shader.h"
#include "vertex_array.h"

class Renderer : NonCopyable {
public:
    static Renderer &getInstance();

    void update();

    void clear();

    void test();

    sol::table getLuaTable(sol::state &lua);

private:
    Renderer();

    Window &window = Window::getInstance();
    BasicShader &shader = BasicShader::getInstance();

    float clearColor[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    VertexArray vao;
};

#endif //HARUJION_RENDERER_H
