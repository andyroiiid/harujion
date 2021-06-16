local Flappy = require("flappy/flappy.lua")
local TopDown = require("topdown/topdown.lua")

local KEY_1 = 49
local KEY_2 = 50
local KEY_ESCAPE = 256

local game

local function reset()
    game = nil

    haru.window.setTitle("Sample Games")
    haru.camera.setHalfHeight(1.0)
    haru.camera.setCenter(0.0, 0.0)
    haru.renderer.setClearColor(0.0, 0.0, 0.0)
end

function haru.init()
    reset()
end

function haru.shutdown()
end

function haru.update(deltaTime)
    if not game then
        if haru.input.keyJustPressed(KEY_1) then
            game = Flappy()
        elseif haru.input.keyJustPressed(KEY_2) then
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
    else
        game:draw()
    end
end
