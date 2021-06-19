local Object = require("classic.lua")

local Bullet = Object:extend()

local texture = haru.Texture.load("topdown/bullet.png", true, true, true)

local SPEED = 320
local LIFETIME = 1.0

function Bullet:new(x, y, r)
    self.sprite = haru.Sprite.new(texture)
    self.x = x
    self.y = y
    self.r = r
    self.ttl = LIFETIME
end

function Bullet:update(deltaTime)
    local distance = SPEED * deltaTime
    self.x = self.x + math.cos(self.r) * distance
    self.y = self.y + math.sin(self.r) * distance
    self.ttl = self.ttl - deltaTime
end

function Bullet:dying()
    return self.ttl <= 0
end

function Bullet:draw()
    self.sprite:draw(self.x, self.y)
end

return Bullet
