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

function BulletManager:hitTest(x0, y0, x1, y1)
    for i, v in ipairs(self.bullets) do
        if x0 <= v.x and v.x <= x1 and y0 <= v.y and v.y <= y1 then
            table.remove(self.bullets, i)
            return v
        end
    end
end

return BulletManager
