local Object = require("classic.lua")

local Enemy = require("topdown/enemy.lua")

local EnemyManager = Object:extend()

function EnemyManager:new(bullets)
    self.enemies = {}
    self.bullets = bullets
end

function EnemyManager:spawn(x, y)
    local enemy = Enemy(x, y)
    table.insert(self.enemies, enemy)
end

function EnemyManager:update(deltaTime, player)
    for i = #self.enemies, 1, -1 do
        local enemy = self.enemies[i]
        local bullet = self.bullets:hitTest(enemy:getBounds())
        if bullet then
            enemy:hit()
        end
        enemy:update(deltaTime, player)
        if enemy:dying() then
            table.remove(self.enemies, i)
        end
    end
end

function EnemyManager:draw()
    for i, v in ipairs(self.enemies) do
        v:draw()
    end
end

return EnemyManager
