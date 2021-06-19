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

local Button = require("button.lua")
local Flappy = require("flappy/flappy.lua")
local TopDown = require("topdown/topdown.lua")

local font = haru.SpriteFont.new("monogram.png")

local KEY_ESCAPE = 256

local flappyButton = Button(0, 40, "Flappy", "SPACE or LEFT CLICK to jump")
local topDownButton = Button(0, -40, "TopDown", "WASD to move, aim with MOUSE")
local game

local function reset()
    game = nil

    haru.window.setTitle("Sample Games")
    haru.camera.setHalfHeight(96)
    haru.camera.setCenter(0.0, 0.0)
    haru.input.setCursor(true)
    haru.renderer.setClearColor(0.0, 0.0, 0.0)
end

function haru.init()
    reset()
end

function haru.shutdown()
end

function haru.update(deltaTime)
    if not game then
        local mouseX, mouseY = haru.input.mouseWorldPosition()
        if flappyButton:update(mouseX, mouseY) then
            game = Flappy()
        end
        if topDownButton:update(mouseX, mouseY) then
            game = TopDown()
        end
    else
        if haru.input.keyJustPressed(KEY_ESCAPE) then
            reset()
        else
            game:update(deltaTime)
        end
    end
end

function haru.draw()
    if not game then
        flappyButton:draw()
        topDownButton:draw()
        font:draw(-96, 64, "ESCAPE to return to menu")
    else
        game:draw()
    end
end
