local Object = require("classic.lua")

local Rect = require("ui/rect.lua")

local Button = Object:extend()

local font = haru.SpriteFont.new("ui/monogram_shadow.png")
local fontWidth, fontHeight = font:getGlyphPixelSize()

local NORMAL_STATE = 0
local HOVER_STATE = 1
local PRESSED_STATE = 2

function Button:new(aMinX, aMinY, aMaxX, aMaxY, left, bottom, right, top)
    self.rect = Rect(aMinX, aMinY, aMaxX, aMaxY)
    self.rect:setPadding(left, bottom, right, top)
    self.x0 = 0
    self.y0 = 0
    self.x1 = 0
    self.y1 = 0
    self.state = NORMAL_STATE
end

function Button.fullRect(text, onPressed)
    local button = Button(0, 0, 1, 1, 0, 0, 0, 0)
    button.text = text
    button.onPressed = onPressed
    return button
end

function Button:updateLayout(x0, y0, x1, y1)
    self.x0, self.y0, self.x1, self.y1 = self.rect:layout(x0, y0, x1, y1)
end

function Button:handleMouse(mouseX, mouseY, pressed)
    if self.x0 <= mouseX and self.y0 <= mouseY and mouseX <= self.x1 and mouseY <= self.y1 then
        if pressed then
            self.state = PRESSED_STATE
        else
            if self.state == PRESSED_STATE and self.onPressed then
                self.onPressed()
            end
            self.state = HOVER_STATE
        end
    else
        self.state = NORMAL_STATE
    end
end

function Button:draw()
    if self.state == NORMAL_STATE then
        haru.renderer.setDrawColor(7 / 255, 24 / 255, 33 / 255, 0.5)
    elseif self.state == HOVER_STATE then
        haru.renderer.setDrawColor(7 / 255, 24 / 255, 33 / 255, 0.6)
    elseif self.state == PRESSED_STATE then
        haru.renderer.setDrawColor(7 / 255, 24 / 255, 33 / 255, 0.7)
    else
        haru.renderer.setDrawColor(7 / 255, 24 / 255, 33 / 255, 0.4)
    end
    haru.renderer.fillRect(self.x0, self.y0, self.x1, self.y1)
    haru.renderer.setDrawColor(1.0, 1.0, 1.0)
    haru.renderer.drawRect(self.x0, self.y0, self.x1, self.y1, 2)
    if self.text then
        font:draw((self.x0 + self.x1) / 2 - #self.text * fontWidth, (self.y0 + self.y1) / 2 - fontHeight, self.text, 2)
    end
end

return Button
