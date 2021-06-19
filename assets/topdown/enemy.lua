local mathf = require("mathf.lua")
local vec2 = require("vec2.lua")

local Object = require("classic.lua")

local Enemy = Object:extend()

local texture = haru.Texture.load("topdown/zombie1_hold.png", true, true, true)

local SPEED = 160

function Enemy:new(x, y)
    self.sprite = haru.Sprite.new(texture)
    self.speed = 0
    self.x = x
    self.y = y
    self.r = 0
    self.hp = 100
end

function Enemy:update(deltaTime, player)
    self.speed = mathf.mix(self.speed, SPEED, 2.0 * deltaTime)
    local dx = player.x - self.x
    local dy = player.y - self.y
    dx, dy = vec2.normalize(dx, dy)
    self.x = self.x + self.speed * dx * deltaTime
    self.y = self.y + self.speed * dy * deltaTime
    self.r = math.atan2(dy, dx)
end

function Enemy:getBounds()
    return self.x - 16, self.y - 16, self.x + 16, self.y + 16
end

function Enemy:hit()
    self.speed = 0.0
    self.hp = self.hp - 25
end

function Enemy:dying()
    return self.hp <= 0
end

function Enemy:draw()
    self.sprite:draw(self.x, self.y, self.r)
end

return Enemy
