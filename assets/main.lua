require("strict.lua")

local NinePatch = require("nine_patch.lua")
local Rect = require("rect.lua")

local texture = haru.Texture.load("blue.png")
local ninePatch = NinePatch(texture, 4, 6, 4, 4)
local rect1 = Rect(0, 0, 0.5, 1)
rect1:setPadding(32, 32, -16, -32)
local rect2 = Rect(0.5, 0, 1, 1)
rect2:setPadding(16, 32, -32, -32)
local rect3 = Rect(0.5, 0.5, 0.5, 0.5)
rect3:setPadding(-32, -32, 32, 32)

function haru.init()
    haru.renderer.setDrawColor(1.0, 1.0, 1.0, 0.5)
end

function haru.shutdown()
end

function haru.update(deltaTime)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    haru.renderer.setMatrixOrtho(0, width, 0, height)

    local x0, y0, x1, y1 = rect1:layout(0, 0, width, height)
    haru.renderer.fillRect(x0, y0, x1, y1)
    haru.renderer.fillRect(rect1:layout(x0, y0, x1, y1))

    haru.renderer.fillRect(rect2:layout(0, 0, width, height))

    ninePatch:draw(rect3:layout(0, 0, width, height))
end
