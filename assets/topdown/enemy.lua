local vec2 = require("vec2.lua")

local Object = require("classic.lua")

local Enemy = Object:extend()

local SPEED = 5.0

function Enemy:new(x, y)
    self.x = x
    self.y = y
end

function Enemy:update(deltaTime, player)
    local dx = player.x - self.x
    local dy = player.y - self.y
    dx, dy = vec2.normalize(dx, dy)
    self.x = self.x + SPEED * dx * deltaTime
    self.y = self.y + SPEED * dy * deltaTime
end

function Enemy:getBounds()
    return self.x - 1.0, self.y - 1.0, self.x + 1.0, self.y + 1.0
end

function Enemy:draw()
    haru.renderer.setDrawColor(1.0, 1.0, 1.0, 0.5)
    haru.renderer.fillRect(self:getBounds())
    haru.renderer.setDrawColor(1.0, 1.0, 1.0)
    haru.renderer.drawRect(self:getBounds())
end

return Enemy
