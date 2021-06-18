local Object = require("classic.lua")

local Player = require("topdown/player.lua")
local BulletManager = require("topdown/bullet_manager.lua")
local EnemyManager = require("topdown/enemy_manager.lua")

local TopDown = Object:extend()

function TopDown:new()
    haru.window.setTitle("TopDown")
    haru.camera.setHalfHeight(10.0)
    haru.input.setCursor(false)

    self.player = Player()
    self.bullets = BulletManager()
    self.enemies = EnemyManager(self.bullets)
    self.crosshair = haru.Sprite.new("topdown/crosshair010.png", 32)
    self.spawnTimer = 2.0
end

function TopDown:update(deltaTime)
    self.spawnTimer = self.spawnTimer - deltaTime
    if self.spawnTimer <= 0.0 then
        self.spawnTimer = self.spawnTimer + 2.0
        self.enemies:spawn(
            -10.0 + 20.0 * math.random(),
            -10.0 + 20.0 * math.random()
        )
    end

    if haru.input.mouseButtonJustPressed(0) then
        local bulletX, bulletY = self.player:getBarrelPos()
        self.bullets:spawn(bulletX, bulletY, self.player.rotation)
    end

    self.player:update(deltaTime)
    self.bullets:update(deltaTime)
    self.enemies:update(deltaTime, self.player)
end

function TopDown:draw()
    haru.renderer.setDrawColor(1.0, 0.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 5.0, 0.0)
    haru.renderer.setDrawColor(0.0, 1.0, 0.0)
    haru.renderer.drawLine(0.0, 0.0, 0.0, 5.0)

    self.player:draw()
    self.bullets:draw()
    self.enemies:draw()

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    self.crosshair:draw(mouseX, mouseY, 0.0)
end

return TopDown
