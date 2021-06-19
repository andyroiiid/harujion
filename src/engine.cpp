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
    loadStrictLua();
}

void Engine::createBindings() {
    haru = lua.create_table("haru");
    bindModules();
    bindTypes();
}

void Engine::bindModules() {
    haru["window"] = window.getLuaTable(lua);
    haru["camera"] = camera.getLuaTable(lua);
    haru["input"] = input.getLuaTable(lua);
    haru["renderer"] = renderer.getLuaTable(lua);
    haru["audio"] = fmodAudio.getLuaTable(lua);
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

void Engine::loadStrictLua() {
    static const char *STRICT_LUA = R"LUA(
-- strict.lua
-- checks uses of undeclared global variables
-- All global variables must be 'declared' through a regular assignment
-- (even assigning nil will do) in a main chunk before being used
-- anywhere or assigned to inside a function.
-- distributed under the Lua license: http://www.lua.org/license.html

local getinfo, error, rawset, rawget = debug.getinfo, error, rawset, rawget

local mt = getmetatable(_G)
if mt == nil then
  mt = {}
  setmetatable(_G, mt)
end

mt.__declared = {}

local function what ()
  local d = getinfo(3, "S")
  return d and d.what or "C"
end

mt.__newindex = function (t, n, v)
  if not mt.__declared[n] then
    local w = what()
    if w ~= "main" and w ~= "C" then
      error("assign to undeclared variable '"..n.."'", 2)
    end
    mt.__declared[n] = true
  end
  rawset(t, n, v)
end

mt.__index = function (t, n)
  if not mt.__declared[n] and what() ~= "C" then
    error("variable '"..n.."' is not declared", 2)
  end
  return rawget(t, n)
end
)LUA";
    checkLua(lua.script(STRICT_LUA, "strict.lua"), true);
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
    input.update();
    glfwPollEvents();
    checkLua(haru["update"](deltaTime));
    camera.update();
}

void Engine::draw() {
    renderer.clear();
    checkLua(haru["draw"]());
    window.swapBuffers();
}
