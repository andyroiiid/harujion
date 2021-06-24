local Object = require("classic.lua")

local Rect = require("ui/rect.lua")

local Text = Object:extend()

local font = haru.SpriteFont.new("ui/monogram_shadow.png")
local fontWidth, fontHeight = font:getGlyphPixelSize()

function Text:new(aMinX, aMinY, aMaxX, aMaxY, left, bottom, right, top, text)
    self.rect = Rect(aMinX, aMinY, aMaxX, aMaxY)
    self.rect:setPadding(left, bottom, right, top)
    self.x0 = 0
    self.y0 = 0
    self.x1 = 0
    self.y1 = 0
    self.text = text
    self.sPrefer = 2
    self.s = self.sPrefer
end

function Text.fullRect(text)
    return Text(0, 0, 1, 1, 0, 0, 0, 0, text)
end

function Text:updateLayout(x0, y0, x1, y1)
    local x0, y0, x1, y1 = self.rect:layout(x0, y0, x1, y1)
    self.x0 = x0
    self.y0 = y0
    self.x1 = x1
    self.y1 = y1
    local sx = (x1 - x0) / (#self.text * fontWidth)
    local sy = (y1 - y0) / fontHeight
    self.s = math.min(sx, sy, self.sPrefer)
end

function Text:handleMouse(mouseX, mouseY, pressed)
end

function Text:draw()
    font:draw(
        (self.x0 + self.x1 - #self.text * fontWidth * self.s) / 2,
        (self.y0 + self.y1 - fontHeight * self.s) / 2,
        self.text,
        self.s
    )
end

return Text
