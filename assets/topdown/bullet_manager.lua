local Object = require("classic.lua")

local Bullet = require("topdown/bullet.lua")

local BulletManager = Object:extend()

function BulletManager:new()
    self.bullets = {}
end

function BulletManager:spawn(x, y, direction)
    local bullet = Bullet(x, y, direction)
    table.insert(self.bullets, bullet)
end

function BulletManager:update(deltaTime)
    for i = #self.bullets, 1, -1 do
        local bullet = self.bullets[i]
        bullet:update(deltaTime)
        if bullet:dying() then
            table.remove(self.bullets, i)
        end
    end
end

function BulletManager:draw()
    for i, v in ipairs(self.bullets) do
        v:draw()
    end
end

return BulletManager
