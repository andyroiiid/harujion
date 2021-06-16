local Object = require("classic.lua")

local Player = require("topdown/player.lua")

local TopDown = Object:extend()

function TopDown:new()
    haru.window.setTitle("TopDown")
    haru.camera.setHalfHeight(10.0)
    self.crosshair = haru.Sprite.new("topdown/crosshair010.png", 32)
    self.player = Player()
end

function TopDown:update(deltaTime)
    self.player:update(deltaTime)
end

function TopDown:draw()
    haru.renderer.setDrawColor(1.0, 0.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 5.0, 0.0)
    haru.renderer.setDrawColor(0.0, 1.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 0.0, 5.0)

    self.player:draw()

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    self.crosshair:draw(mouseX, mouseY, 0.0)
end

return TopDown
