//
// Created by andyroiiid on 6/13/2021.
//

#include "engine.h"

#include <spdlog/spdlog.h>

#include "renderer/texture.h"
#include "renderer/sprite/sprite.h"
#include "renderer/sprite/sprite_font.h"

Engine &Engine::getInstance() {
    static Engine instance;
    return instance;
}

Engine::Engine() {
    lua.open_libraries(
            sol::lib::base,
            sol::lib::package,
            sol::lib::coroutine,
            sol::lib::string,
            sol::lib::os,
            sol::lib::math,
            sol::lib::table,
            sol::lib::debug,
            sol::lib::bit32,
            sol::lib::io,
            sol::lib::ffi,
            sol::lib::jit,
            sol::lib::utf8
    );
    lua.add_package_loader(Physfs::luaPackageLoader);
    createBindings();
    loadPrelude();
}

void Engine::createBindings() {
    haru = lua.create_table("haru");
    window.bindFunctions(haru);
    camera.bindFunctions(haru);
    keyboard.bindFunctions(haru);
    mouse.bindFunctions(haru);
    renderer.bindFunctions(haru);
    fmodAudio.bindFunctions(haru);
    bindTypes();
}

void Engine::bindTypes() {
    sol::usertype<Texture> texture = haru.new_usertype<Texture>(
            "Texture",
            sol::constructors<Texture(const std::string &, bool, bool, bool)>()
    );
    texture.set_function("_load", Texture::load);

    sol::usertype<Sprite> sprite = haru.new_usertype<Sprite>(
            "Sprite",
            sol::constructors<Sprite(std::shared_ptr<Texture> &)>()
    );
    sprite["setPixelRect"] = &Sprite::setPixelRect;
    sprite["setPixelPivot"] = &Sprite::setPixelPivot;
    sprite["setFlip"] = &Sprite::setFlip;
    sprite["_draw"] = &Sprite::draw;

    sol::usertype<SpriteFont> spriteFont = haru.new_usertype<SpriteFont>(
            "SpriteFont",
            sol::constructors<SpriteFont(const std::string &)>());
    spriteFont["draw"] = &SpriteFont::draw;
}

void Engine::checkLua(const sol::protected_function_result &result, bool abortOnError) {
    if (result.valid()) return;

    sol::error error = result;
    spdlog::error("lua error: {}", error.what());

    if (abortOnError) {
        exit(EXIT_FAILURE);
    }
}

void Engine::loadPrelude() {
    static const char *PRELUDE_LUA = R"LUA(
function haru.renderer.setClearColor(r, g, b, a)
    a = a or 1.0
    return haru.renderer._setClearColor(r, g, b, a)
end

function haru.renderer.setDrawColor(r, g, b, a)
    a = a or 1.0
    return haru.renderer._setDrawColor(r, g, b, a)
end

function haru.Texture.load(filename, filter, clamp, mipmap)
    filter = filter or false
    clamp = clamp or false
    mipmap = mipmap or false
    return haru.Texture._load(filename, filter, clamp, mipmap)
end

function haru.Sprite:draw(x, y, r, sx, sy)
    r = r or 0.0
    sx = sx or 1.0
    sy = sy or 1.0
    return self:_draw(x, y, r, sx, sy)
end
)LUA";
    checkLua(lua.script(PRELUDE_LUA, "prelude.lua"), true);
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
    keyboard.update();
    mouse.update();
    glfwPollEvents();
    checkLua(haru["update"](deltaTime));
    camera.update();
}

void Engine::draw() {
    renderer.clear();
    checkLua(haru["draw"]());
    window.swapBuffers();
}
