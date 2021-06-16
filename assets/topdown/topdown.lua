local Object = require("classic.lua")

local Player = require("topdown/player.lua")
local Enemy = require("topdown/enemy.lua")
local BulletManager = require("topdown/bullet_manager.lua")

local TopDown = Object:extend()

function TopDown:new()
    haru.window.setTitle("TopDown")
    haru.camera.setHalfHeight(10.0)
    haru.input.setCursor(false)

    self.player = Player()
    self.enemy = Enemy(3.0, 4.0)
    self.bullets = BulletManager()
    self.crosshair = haru.Sprite.new("topdown/crosshair010.png", 32)
end

function TopDown:update(deltaTime)
    if haru.input.mouseButtonJustPressed(0) then
        local bulletX, bulletY = self.player:getBarrelPos()
        self.bullets:spawn(bulletX, bulletY, self.player.rotation)
    end

    self.player:update(deltaTime)
    self.enemy:update(deltaTime, self.player)
    self.bullets:update(deltaTime)

    local bullet = self.bullets:hitTest(self.enemy:getBounds())
    if bullet then
        self.enemy:hit()
    end
end

function TopDown:draw()
    haru.renderer.setDrawColor(1.0, 0.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 5.0, 0.0)
    haru.renderer.setDrawColor(0.0, 1.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 0.0, 5.0)

    self.player:draw()
    self.enemy:draw()
    self.bullets:draw()

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    self.crosshair:draw(mouseX, mouseY, 0.0)
end

return TopDown
