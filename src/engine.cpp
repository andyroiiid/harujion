//
// Created by andyroiiid on 6/13/2021.
//

#include "engine.h"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

Engine &Engine::getInstance() {
    static Engine instance;
    return instance;
}

Engine::Engine() {
    physfs.mount("assets", "/");
    initEnv();
}

void Engine::initEnv() {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
    lua.add_package_loader(Physfs::luaPackageLoader);

    haru = lua.create_table("haru");
    haru["clearColor"] = std::ref(renderer.clearColor);
    haru.set_function("setTitle", [this](const char *title) { window.setTitle(title); });
}

void Engine::checkLua(const sol::protected_function_result &result, bool abortOnError) {
    if (result.valid()) return;

    sol::error error = result;
    spdlog::error("lua error: {}", error.what());

    if (abortOnError) {
        exit(EXIT_FAILURE);
    }
}

void Engine::loadScript(const std::string &filename) {
    checkLua(lua.script(physfs.readFile(filename), filename), true);
}

void Engine::mainLoop() {
    loadScript("main.lua");

    checkLua(haru["init"]());
    double prevTime = glfwGetTime();
    while (!window.shouldClose()) {
        double currTime = glfwGetTime();
        update(static_cast<float>(currTime - prevTime));
        prevTime = currTime;
        draw();
    }
    checkLua(haru["shutdown"]());
}

void Engine::update(float deltaTime) {
    glfwPollEvents();
    checkLua(haru["update"](deltaTime));
}

void Engine::draw() {
    renderer.clear();
    checkLua(haru["draw"]());
    window.swapBuffers();
}