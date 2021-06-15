local Flappy = require("flappy/flappy.lua")

local game

function haru.init()
    game = Flappy()
end

function haru.shutdown()
end

function haru.update(deltaTime)
    game:update(deltaTime)
end

function haru.draw()
    game:draw()
end
