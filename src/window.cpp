//
// Created by andyroiiid on 6/13/2021.
//

#include "window.h"

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

Window &Window::getInstance() {
    static Window instance;
    return instance;
}

Window::Window() {
    glfwSetErrorCallback([](int error, const char *description) {
        spdlog::error("glfw error {}: {}", error, description);
    });

    if (!glfwInit()) {
        spdlog::error("failed to init glfw");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(
            800,
            600,
            "harujion",
            nullptr,
            nullptr
    );
    if (!window) {
        spdlog::error("failed to create window");
        return;
    }
    glfwSetWindowSizeLimits(window, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGL(glfwGetProcAddress)) {
        spdlog::error("failed to load glad");
        return;
    }
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::setTitle(const char *title) {
    glfwSetWindowTitle(window, title);
}
