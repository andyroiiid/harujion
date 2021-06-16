local vec2 = require("vec2.lua")

local Object = require("classic.lua")

local Player = Object:extend()

local KEY_A = 65
local KEY_D = 68
local KEY_S = 83
local KEY_W = 87

function Player:new()
    self.sprite = haru.Sprite.new("topdown/survivor1_gun.png", 32)
    self.sprite:setPixelPivot(16.5, 21.5)
    self.x = 0.0
    self.y = 0.0
    self.rotation = 0.0
end

function Player:getBarrelPos()
    local x, y = vec2.rotate(33.5 / 32.0, -9.5 / 32.0, self.rotation)
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

    self.x = self.x + 10.0 * horizontal * deltaTime
    self.y = self.y + 10.0 * vertical * deltaTime

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    self.rotation = math.atan2(mouseY - self.y, mouseX - self.x)

    haru.camera.setCenter(self.x, self.y)
end

function Player:draw()
    self.sprite:draw(self.x, self.y, self.rotation)
end

return Player