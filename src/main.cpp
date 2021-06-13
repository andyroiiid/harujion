#include <GLFW/glfw3.h>
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

#include "physfs.h"
#include "window.h"
#include "renderer.h"

void checkLuaResult(const sol::protected_function_result &result) {
    if (!result.valid()) {
        sol::error error = result;
        spdlog::error("lua error: {}", error.what());
        exit(EXIT_FAILURE);
    }
}

int main() {
    auto &physfs = Physfs::getInstance();
    physfs.mount("assets", "/");

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
    lua.add_package_loader(Physfs::luaPackageLoader);

    sol::table haru = lua.create_table("haru");
    auto &renderer = Renderer::getInstance();
    haru["clearColor"] = std::ref(renderer.clearColor);

    auto &window = Window::getInstance();
    auto result = lua.script(physfs.readFile("main.lua"), "main.lua");
    checkLuaResult(result);

    lua.script("for k, v in pairs(haru) do print(k, v) end");
    checkLuaResult(result);

    double prevTime = glfwGetTime();
    while (!window.shouldClose()) {
        window.pollEvents();

        double currTime = glfwGetTime();
        auto deltaTime = static_cast<float>(currTime - prevTime);
        result = haru["update"](deltaTime);
        checkLuaResult(result);
        prevTime = currTime;

        renderer.clear();

        result = haru["draw"]();
        checkLuaResult(result);

        window.swapBuffers();
    }

    return EXIT_SUCCESS;
}
