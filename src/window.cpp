//
// Created by andyroiiid on 6/13/2021.
//

#include "window.h"

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
    glfwWindow = glfwCreateWindow(
            800,
            600,
            "harujion",
            nullptr,
            nullptr
    );
    if (!glfwWindow) {
        spdlog::error("failed to create window");
        return;
    }
    glfwSetWindowSizeLimits(glfwWindow, 320, 240, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);

    if (!gladLoadGL(glfwGetProcAddress)) {
        spdlog::error("failed to load glad");
        return;
    }
}

Window::~Window() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

void Window::swapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

std::tuple<int, int> Window::getFramebufferSize() {
    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);
    return std::make_tuple(width, height);
}

void Window::setTitle(const char *title) {
    glfwSetWindowTitle(glfwWindow, title);
}
