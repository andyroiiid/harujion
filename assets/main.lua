function haru.renderer.setClearColor(r, g, b, a)
    a = a or 1.0
    haru.renderer._setClearColor(r, g, b, a)
end

function haru.renderer.setDrawColor(r, g, b, a)
    a = a or 1.0
    haru.renderer._setDrawColor(r, g, b, a)
end

function haru.Sprite:draw(x, y, r)
    r = r or 0.0
    self:_draw(x, y, r)
end

local Button = require("button.lua")
local Flappy = require("flappy/flappy.lua")
local TopDown = require("topdown/topdown.lua")

local font = haru.SpriteFont.new("monogram.png", 32)

local KEY_ESCAPE = 256

local flappyButton = Button(0.0, 1.25, "Flappy", "SPACE or LEFT CLICK to jump")
local topDownButton = Button(0.0, -1.25, "TopDown", "WASD to move, aim with MOUSE")
local game

local function reset()
    game = nil

    haru.window.setTitle("Sample Games")
    haru.camera.setHalfHeight(3.0)
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
        font:draw(-3.0, 2.0, "ESCAPE to return to menu")
    else
        game:draw()
    end
end
