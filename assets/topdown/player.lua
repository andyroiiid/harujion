local vec2 = require("vec2.lua")

local Object = require("classic.lua")

local Player = Object:extend()

local texture = haru.Texture.load("topdown/survivor1_gun.png", true, true, true)

local KEY_A = 65
local KEY_D = 68
local KEY_S = 83
local KEY_W = 87

local SPEED = 10.0
local BARREL_X = 33.5 / 32.0
local BARREL_Y = -9.5 / 32.0

function Player:new()
    self.sprite = haru.Sprite.new(texture, 32)
    self.sprite:setPixelPivot(16.5, 21.5)
    self.x = 0.0
    self.y = 0.0
    self.rotation = 0.0
end

function Player:getBarrelPos()
    local x, y = vec2.rotate(BARREL_X, BARREL_Y, self.rotation)
    return self.x + x, self.y + y
end

local function getInputVector()
    local horizontal = 0.0
    local vertical = 0.0
    if haru.input.keyPressed(KEY_W) then
        vertical = vertical + 1.0
    end
    if haru.input.keyPressed(KEY_S) then
        vertical = vertical - 1.0
    end
    if haru.input.keyPressed(KEY_D) then
        horizontal = horizontal + 1.0
    end
    if haru.input.keyPressed(KEY_A) then
        horizontal = horizontal - 1.0
    end
    return vec2.normalize(horizontal, vertical)
end

function Player:update(deltaTime)
    local horizontal, vertical = getInputVector()

    self.x = self.x + SPEED * horizontal * deltaTime
    self.y = self.y + SPEED * vertical * deltaTime

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    self.rotation = math.atan2(mouseY - self.y, mouseX - self.x)

    haru.camera.setCenter(self.x, self.y)
end

function Player:draw()
    self.sprite:draw(self.x, self.y, self.rotation)
end

return Player
