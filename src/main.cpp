#include <spdlog/spdlog.h>
#include <sol/sol.hpp>
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "physfs.h"

int main() {
    auto &physfs = Physfs::getInstance();
    physfs.mount("assets", "/");

    {
        sol::state lua;

        lua.open_libraries(sol::lib::base, sol::lib::package);
        lua.add_package_loader(Physfs::luaPackageLoader);

        auto result = lua.do_string(physfs.readFile("main.lua"));
        if (result.valid()) {
            spdlog::info("succeed");
        } else {
            sol::error error = result;
            spdlog::error("failed: {}", error.what());
        }
    }

    glfwInit();

    GLFWwindow *window = glfwCreateWindow(800, 600, "harujion", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    spdlog::info("GL_VERSION: {}", glGetString(GL_VERSION));
    spdlog::info("GL_SHADING_LANGUAGE_VERSION: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    spdlog::info("GL_VENDOR: {}", glGetString(GL_VENDOR));
    spdlog::info("GL_RENDERER: {}", glGetString(GL_RENDERER));

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
