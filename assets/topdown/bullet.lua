local Object = require("classic.lua")

local Bullet = Object:extend()

local SPEED = 20.0
local LIFETIME = 5.0

function Bullet:new(x, y, direction)
    self.sprite = haru.Sprite.new("topdown/bullet.png", 32)
    self.x = x
    self.y = y
    self.direction = direction
    self.age = 0.0
end

function Bullet:update(deltaTime)
    local distance = SPEED * deltaTime
    self.x = self.x + math.cos(self.direction) * distance
    self.y = self.y + math.sin(self.direction) * distance
    self.age = self.age + deltaTime
    return self.age > LIFETIME
end

function Bullet:draw()
    self.sprite:draw(self.x, self.y, 0.0)
end

return Bullet
