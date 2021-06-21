require("strict.lua")

local NinePatch = require("nine_patch.lua")

local texture = haru.Texture.load("blue.png")
local ninePatch = NinePatch(texture, 16, 16, 16, 16)

function haru.init()
end

function haru.shutdown()
end

function haru.update(deltaTime)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    haru.renderer.setMatrixOrtho(0, width, 0, height)
    ninePatch:draw(width / 2, height / 2, 128, 64)
    ninePatch:draw(width / 2 - 128, height / 2, 128, 64)
end
