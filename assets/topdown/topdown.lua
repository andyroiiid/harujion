local Object = require("classic.lua")

local Player = require("topdown/player.lua")
local BulletManager = require("topdown/bullet_manager.lua")
local EnemyManager = require("topdown/enemy_manager.lua")

local TopDown = Object:extend()

local crosshairTexture = haru.Texture.load("topdown/crosshair010.png")

function TopDown:new()
    haru.window.setTitle("TopDown")
    camera:setHalfHeight(320)
    haru.mouse.setCursor(false)

    self.player = Player()
    self.bullets = BulletManager()
    self.enemies = EnemyManager(self.bullets)
    self.crosshair = haru.Sprite.new(crosshairTexture)
    self.spawnTimer = 2.0
end

function TopDown:update(deltaTime)
    self.spawnTimer = self.spawnTimer - deltaTime
    if self.spawnTimer <= 0.0 then
        self.spawnTimer = self.spawnTimer + 2.0
        self.enemies:spawn(
            -320 + 640 * math.random(),
            -320 + 640 * math.random()
        )
    end

    if haru.mouse.justPressed(0) then
        local bulletX, bulletY = self.player:getBarrelPos()
        self.bullets:spawn(bulletX, bulletY, self.player.r)
    end

    self.player:update(deltaTime)
    self.bullets:update(deltaTime)
    self.enemies:update(deltaTime, self.player)
end

function TopDown:draw()
    haru.renderer.setDrawColor(1.0, 0.0, 0.0)
    haru.renderer.drawLine(0, 0, 160, 0)
    haru.renderer.setDrawColor(0.0, 1.0, 0.0)
    haru.renderer.drawLine(0, 0, 0, 160)

    self.player:draw()
    self.bullets:draw()
    self.enemies:draw()

    local mouseX, mouseY = camera:getMousePosition()
    self.crosshair:draw(mouseX, mouseY, 0.0)
end

return TopDown
