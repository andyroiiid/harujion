Object = require("classic.lua")

Player = Object:extend()

function Player:new()
    self.sprites = {
        haru.renderer.Sprite.new("yellowbird-midflap.png", 32),
        haru.renderer.Sprite.new("yellowbird-downflap.png", 32),
        haru.renderer.Sprite.new("yellowbird-midflap.png", 32),
        haru.renderer.Sprite.new("yellowbird-upflap.png", 32)
    }
    self:reset()
end

function Player:reset()
    self.sprite_idx = 1
    self.sprite_timer = 0.0
    self.v = 0.0
    self.y = 0.0
end

function Player:jump()
    self.v = 5.0
end

function Player:update(deltaTime)
    self.v = self.v - 10 * deltaTime
    self.y = self.y + self.v * deltaTime

    self.sprite_timer = self.sprite_timer + deltaTime
    if self.sprite_timer > 0.1 then
        self.sprite_timer = self.sprite_timer - 0.1

        self.sprite_idx = self.sprite_idx + 1
        if self.sprite_idx == 5 then
            self.sprite_idx = 1
        end
    end
end

function Player:draw()
    self.sprites[self.sprite_idx]:draw(0.0, self.y, self.v * 0.1)
end

player = Player()
