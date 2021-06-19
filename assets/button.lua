local Object = require("classic.lua")

local Button = Object:extend()

local font = haru.SpriteFont.new("monogram.png")
local texture = haru.Texture.load("blue.png")
local sprite = haru.Sprite.new(texture)
local pressedTexture = haru.Texture.load("blue_pressed.png")
local pressedSprite = haru.Sprite.new(pressedTexture)

function Button:new(x, y, text, description)
    self.x = x
    self.y = y
    self.text = text
    self.description = description
    self.pressed = false
end

function Button:update(mouseX, mouseY)
    if mouseX < self.x - 48 or mouseX > self.x + 48 or mouseY < self.y - 24 or mouseY > self.y + 24 then
        self.pressed = false
    else
        self.pressed = haru.mouse.pressed(0)
        if haru.mouse.justReleased(0) then
            return true
        end
    end
    return false
end

function Button:draw()
    if self.pressed then
        pressedSprite:draw(self.x, self.y)
        font:draw(self.x - 32, self.y - 10, self.text)
    else
        sprite:draw(self.x, self.y, 0.0)
        font:draw(self.x - 32, self.y - 8, self.text)
    end

    font:draw(self.x - 112, self.y - 48, self.description)
end

return Button
