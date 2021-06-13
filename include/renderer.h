//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_RENDERER_H
#define HARUJION_RENDERER_H

#include <sol/forward.hpp>

#include "non_copyable.h"
#include "window.h"
#include "dynamic_draw_shader.h"
#include "sprite_shader.h"
#include "vertex_array.h"
#include "texture.h"

class Renderer : NonCopyable {
public:
    static Renderer &getInstance();

    void update();

    void clear();

    sol::table getLuaTable(sol::state &lua);

    void setClearColor(float r, float g, float b, float a = 1.0f);

    void setDrawColor(float r, float g, float b, float a = 1.0f);

    void drawPoint(float x, float y);

    void drawPoint(float x, float y, float size);

    void drawLine(float x0, float y0, float x1, float y1);

    void drawLine(float x0, float y0, float x1, float y1, float width);

    void test();

private:
    Renderer();

    inline Vertex dynamicDrawVertex(float x, float y) {
        return Vertex{glm::vec2{x, y}, glm::vec2{0.0f, 0.0f}, drawColor};
    }

    void dynamicDraw(std::initializer_list<Vertex> vertices, GLenum mode);

    Window &window = Window::getInstance();
    DynamicDrawShader &dynamicDrawShader = DynamicDrawShader::getInstance();
    SpriteShader &spriteShader = SpriteShader::getInstance();

    glm::vec4 clearColor = {0.2f, 0.2f, 0.2f, 1.0f};
    glm::vec4 drawColor = {1.0f, 1.0f, 1.0f, 1.0f};

    VertexArray dynamicDrawVao;
    VertexArray spriteVao;

    std::shared_ptr<Texture> texture;
};

#endif //HARUJION_RENDERER_H
