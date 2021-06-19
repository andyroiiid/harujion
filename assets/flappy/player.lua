local Object = require("classic.lua")

local Player = Object:extend()

local midFlapTexture = haru.Texture.load("flappy/yellowbird-midflap.png", false, false, false)
local downFlapTexture = haru.Texture.load("flappy/yellowbird-downflap.png", false, false, false)
local upFlapTexture = haru.Texture.load("flappy/yellowbird-upflap.png", false, false, false)

function Player:new()
    self.sprites = {
        haru.Sprite.new(midFlapTexture, 32),
        haru.Sprite.new(downFlapTexture, 32),
        haru.Sprite.new(midFlapTexture, 32),
        haru.Sprite.new(upFlapTexture, 32)
    }
    self.v = 0.0
    self.y = 0.0
    self.sprite_timer = 0.0
    self.sprite_idx = 1
end

function Player:jump()
    self.v = 5.0
end

function Player:update(deltaTime)
    -- only y movement
    self.v = self.v - 10 * deltaTime
    self.y = self.y + self.v * deltaTime

    -- some primitive sprite frame animation
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

return Player
