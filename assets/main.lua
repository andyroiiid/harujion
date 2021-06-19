require("strict.lua")

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
    haru.mouse.setCursor(true)
    haru.renderer.setClearColor(0.0, 0.0, 0.0)
end

function haru.init()
    reset()
end

function haru.shutdown()
end

function haru.update(deltaTime)
    if not game then
        local mouseX, mouseY = haru.mouse.worldPosition()
        if flappyButton:update(mouseX, mouseY) then
            game = Flappy()
        end
        if topDownButton:update(mouseX, mouseY) then
            game = TopDown()
        end
    else
        if haru.keyboard.justPressed(KEY_ESCAPE) then
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
