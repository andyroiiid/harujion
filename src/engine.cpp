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
    initEnv();
}

void Engine::initEnv() {
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::math, sol::lib::table);
    lua.add_package_loader(Physfs::luaPackageLoader);

    haru = lua.create_table("haru");
    haru["window"] = window.getLuaTable(lua);
    haru["renderer"] = renderer.getLuaTable(lua);
    haru["audio"] = fmodAudio.getLuaTable(lua);
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
    fmodAudio.update();
    glfwPollEvents();
    checkLua(haru["update"](deltaTime));
    renderer.update();
}

void Engine::draw() {
    renderer.clear();
    checkLua(haru["draw"]());
    window.swapBuffers();
}
