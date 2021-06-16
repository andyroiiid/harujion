local Object = require("classic.lua")

local Player = require("topdown/player.lua")
local Bullet = require("topdown/bullet.lua")

local TopDown = Object:extend()

function TopDown:new()
    haru.window.setTitle("TopDown")
    haru.camera.setHalfHeight(10.0)
    haru.input.setCursor(false)
    self.crosshair = haru.Sprite.new("topdown/crosshair010.png", 32)
    self.player = Player()
    self.bullets = {}
end

function TopDown:update(deltaTime)
    if haru.input.mouseButtonJustPressed(0) then
        local bulletX, bulletY = self.player:getBarrelPos()
        local bullet = Bullet(bulletX, bulletY, self.player.rotation)
        table.insert(self.bullets, bullet)
    end

    self.player:update(deltaTime)

    local dyingBullets = {}
    for i, v in ipairs(self.bullets) do
        if v:update(deltaTime) then
            table.insert(dyingBullets, i)
        end
    end

    for i = #dyingBullets, 1, -1 do
        table.remove(self.bullets, dyingBullets[i])
    end
end

function TopDown:draw()
    haru.renderer.setDrawColor(1.0, 0.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 5.0, 0.0)
    haru.renderer.setDrawColor(0.0, 1.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 0.0, 5.0)

    self.player:draw()

    for i, v in ipairs(self.bullets) do
        v:draw()
    end

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    self.crosshair:draw(mouseX, mouseY, 0.0)
end

return TopDown
