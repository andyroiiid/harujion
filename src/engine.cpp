// Copyright 2021-2025 Andrew Huang. All Rights Reserved.

#include "engine.h"

#include <spdlog/spdlog.h>

#include "renderer/sprite/sprite.h"
#include "renderer/sprite/sprite_font.h"
#include "renderer/texture.h"
#include "renderer/tile/tileset.h"

Engine &Engine::getInstance()
{
    static Engine instance;
    return instance;
}

Engine::Engine()
{
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

void Engine::createBindings()
{
    haru = lua.create_table("haru");

    haru.create_named(
        "window",
        "close",
        [this]
    {
        window.close();
    },
        "getFramebufferSize",
        [this]
    {
        return window.getFramebufferSize();
    },
        "setTitle",
        [this](const char *title)
    {
        window.setTitle(title);
    }
    );

    haru.create_named(
        "keyboard",
        "pressed",
        [this](int key)
    {
        return keyboard.pressed(key);
    },
        "justPressed",
        [this](int key)
    {
        return keyboard.justPressed(key);
    },
        "justReleased",
        [this](int key)
    {
        return keyboard.justReleased(key);
    }
    );

    haru.create_named(
        "mouse",
        "pressed",
        [this](int button)
    {
        return mouse.pressed(button);
    },
        "justPressed",
        [this](int button)
    {
        return mouse.justPressed(button);
    },
        "justReleased",
        [this](int button)
    {
        return mouse.justReleased(button);
    },
        "normalizedPosition",
        [this]()
    {
        return mouse.normalizedPosition();
    },
        "setCursor",
        [this](bool enable)
    {
        return mouse.setCursor(enable);
    }
    );

    haru.create_named(
        "renderer",
        "setMatrixOrtho",
        [this](float left, float right, float bottom, float top)
    {
        renderer.setMatrixOrtho(left, right, bottom, top);
    },
        "_setClearColor",
        [this](float r, float g, float b, float a)
    {
        renderer.setClearColor(r, g, b, a);
    },
        "_setDrawColor",
        [this](float r, float g, float b, float a)
    {
        renderer.setDrawColor(r, g, b, a);
    },
        "drawPoint",
        sol::overload(
            [this](float x, float y)
    {
        renderer.drawPoint(x, y);
    },
            [this](float x, float y, float size)
    {
        renderer.drawPoint(x, y, size);
    }
        ),
        "drawLine",
        sol::overload(
            [this](float x0, float y0, float x1, float y1)
    {
        renderer.drawLine(x0, y0, x1, y1);
    },
            [this](float x0, float y0, float x1, float y1, float width)
    {
        renderer.drawLine(x0, y0, x1, y1, width);
    }
        ),
        "drawRect",
        sol::overload(
            [this](float x0, float y0, float x1, float y1)
    {
        renderer.drawRect(x0, y0, x1, y1);
    },
            [this](float x0, float y0, float x1, float y1, float width)
    {
        renderer.drawRect(x0, y0, x1, y1, width);
    }
        ),
        "fillRect",
        [this](float x0, float y0, float x1, float y1)
    {
        renderer.fillRect(x0, y0, x1, y1);
    }
    );

    haru.create_named(
        "audio",
        "loadBank",
        [this](const std::string &filename)
    {
        fmodAudio.loadBank(filename);
    },
        "setVolume",
        [this](float volume)
    {
        fmodAudio.setVolume(volume);
    },
        "getEventDescription",
        [this](const std::string &eventPath)
    {
        return fmodAudio.getEventDescription(eventPath);
    },
        "fireOneShotEvent",
        &FmodAudio::fireOneShotEvent
    );

    sol::usertype<Texture> texture = haru.new_usertype<Texture>("Texture", sol::constructors<Texture(const std::string &, bool, bool, bool)>());
    texture.set_function(
        "getSize",
        [](const Texture &texture)
    {
        const auto &size = texture.size();
        return std::make_tuple(size.x, size.y);
    }
    );
    texture.set_function("_load", Texture::load);

    sol::usertype<Sprite> sprite = haru.new_usertype<Sprite>("Sprite", sol::constructors<Sprite(std::shared_ptr<Texture> &)>());
    sprite["setPixelRect"]       = &Sprite::setPixelRect;
    sprite["setPixelPivot"]      = &Sprite::setPixelPivot;
    sprite["setFlip"]            = &Sprite::setFlip;
    sprite["_draw"]              = &Sprite::draw;

    sol::usertype<SpriteFont> spriteFont = haru.new_usertype<SpriteFont>("SpriteFont", sol::constructors<SpriteFont(const std::string &)>());
    spriteFont["getGlyphPixelSize"]      = &SpriteFont::getGlyphPixelSize;
    spriteFont["_draw"]                  = &SpriteFont::draw;

    sol::usertype<Tileset> tileset = haru.new_usertype<Tileset>("Tileset", sol::constructors<Tileset(std::shared_ptr<Texture> &, int, int, int)>());
    tileset["getTileSize"]         = &Tileset::getTileSize;
    tileset["draw"]                = &Tileset::draw;
}

void Engine::checkLua(const sol::protected_function_result &result, bool abortOnError)
{
    if (result.valid())
    {
        return;
    }

    sol::error error = result;
    spdlog::error("lua error: {}", error.what());

    if (abortOnError)
    {
        exit(EXIT_FAILURE);
    }
}

void Engine::loadPrelude()
{
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

function haru.SpriteFont:draw(x, y, text, s)
    s = s or 1.0
    return self:_draw(x, y, text, s)
end
)LUA";
    checkLua(lua.script(PRELUDE_LUA, "prelude.lua"), true);
}

void Engine::loadScript(const std::string &filename)
{
    checkLua(lua.script(physfs.readFile(filename), filename), true);
}

void Engine::mainLoop()
{
    loadScript("main.lua");

    checkLua(haru["init"]());
    double prevTime = glfwGetTime();
    while (!window.shouldClose())
    {
        double currTime = glfwGetTime();
        update(static_cast<float>(currTime - prevTime));
        prevTime = currTime;
        draw();
    }
    checkLua(haru["shutdown"]());
}

void Engine::update(float deltaTime)
{
    fmodAudio.update();
    keyboard.update();
    mouse.update();
    glfwPollEvents();
    checkLua(haru["update"](deltaTime));
}

void Engine::draw()
{
    renderer.clear();
    checkLua(haru["draw"]());
    window.swapBuffers();
}
