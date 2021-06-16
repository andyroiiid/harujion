local Object = require("classic.lua")

local Button = Object:extend()

local sprite = haru.Sprite.new("blue.png", 32)
local pressedSprite = haru.Sprite.new("blue_pressed.png", 32)

function Button:new(x, y)
    self.x = x
    self.y = y
    self.pressed = false
end

function Button:update(mouseX, mouseY)
    if mouseX < self.x - 1.5 or mouseX > self.x + 1.5 or mouseY < self.y - 0.75 or mouseY > self.y + 0.75 then
        self.pressed = false
    else
        self.pressed = haru.input.mouseButtonPressed(0)
        if haru.input.mouseButtonJustReleased(0) then
            return true
        end
    end
    return false
end

function Button:draw()
    if self.pressed then
        pressedSprite:draw(self.x, self.y, 0.0)
    else
        sprite:draw(self.x, self.y, 0.0)
    end
end

return Button