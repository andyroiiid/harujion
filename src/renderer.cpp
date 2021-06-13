//
// Created by andyroiiid on 6/13/2021.
//

#include "renderer.h"

#include <glad/gl.h>
#include <spdlog/spdlog.h>

Renderer &Renderer::getInstance() {
    static Renderer instance;
    return instance;
}

Renderer::Renderer() {
#define LOG_GL_STRING(name) spdlog::info(#name ": {}", glGetString(name))
    LOG_GL_STRING(GL_VERSION);
    LOG_GL_STRING(GL_SHADING_LANGUAGE_VERSION);
    LOG_GL_STRING(GL_VENDOR);
    LOG_GL_STRING(GL_RENDERER);
#undef LOG_GL_STRING
}

void Renderer::clear() {
    glClearBufferfv(GL_COLOR, 0, clearColor);
}
