//
// Created by andyroiiid on 6/13/2021.
//

#ifndef HARUJION_ENGINE_H
#define HARUJION_ENGINE_H

#include <sol/sol.hpp>

#include "non_copyable.h"
#include "physfs.h"
#include "window.h"
#include "renderer.h"
#include "fmod_audio.h"

class Engine : NonCopyable {
public:
    static Engine &getInstance();

    void mainLoop();

private:
    Engine();

    void initEnv();

    static void checkLua(const sol::protected_function_result &result, bool abortOnError = false);

    void loadScript(const std::string &filename);

    void update(float deltaTime);

    void draw();

    Physfs &physfs = Physfs::getInstance();
    Window &window = Window::getInstance();
    Renderer &renderer = Renderer::getInstance();
    FmodAudio &fmodAudio = FmodAudio::getInstance();

    sol::state lua;
    sol::table haru;
};

#endif //HARUJION_ENGINE_H
