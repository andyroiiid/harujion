local Object = require("classic.lua")

local Button = Object:extend()

local font = haru.SpriteFont.new("monogram.png", 32)
local texture = haru.Texture.load("blue.png", false, false, false)
local sprite = haru.Sprite.new(texture, 32)
local pressedTexture = haru.Texture.load("blue_pressed.png", false, false, false)
local pressedSprite = haru.Sprite.new(pressedTexture, 32)

function Button:new(x, y, text, description)
    self.x = x
    self.y = y
    self.text = text
    self.description = description
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
        font:draw(self.x - 1.0, self.y - 0.3125, self.text)
    else
        sprite:draw(self.x, self.y, 0.0)
        font:draw(self.x - 1.0, self.y - 0.25, self.text)
    end

    font:draw(self.x - 3.5, self.y - 1.5, self.description)
end

return Button
