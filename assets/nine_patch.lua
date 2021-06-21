local Object = require("classic.lua")

local NinePatch = Object:extend()

function NinePatch:new(texture, left, right, top, bottom)
    self.p0 = haru.Sprite.new(texture)
    self.p1 = haru.Sprite.new(texture)
    self.p2 = haru.Sprite.new(texture)
    self.p3 = haru.Sprite.new(texture)
    self.p4 = haru.Sprite.new(texture)
    self.p5 = haru.Sprite.new(texture)
    self.p6 = haru.Sprite.new(texture)
    self.p7 = haru.Sprite.new(texture)
    self.p8 = haru.Sprite.new(texture)
    local width, height = texture:getSize()
    local a = left
    local b = width - right - left
    local c = right
    local d = bottom
    local e = height - top - bottom
    local f = top
    self.p0:setPixelRect(0,    0,   a, d)
    self.p1:setPixelRect(a,    0,   b, d)
    self.p2:setPixelRect(a+b,  0,   c, d)
    self.p3:setPixelRect(0,    d,   a, e)
    self.p4:setPixelRect(a,    d,   b, e)
    self.p5:setPixelRect(a+b,  d,   c, e)
    self.p6:setPixelRect(0,    d+e, a, f)
    self.p7:setPixelRect(a,    d+e, b, f)
    self.p8:setPixelRect(a+b,  d+e, c, f)
    self.a = a
    self.b = b
    self.c = c
    self.d = d
    self.e = e
    self.f = f
    self.p0:setPixelPivot(0, 0)
    self.p1:setPixelPivot(0, 0)
    self.p2:setPixelPivot(0, 0)
    self.p3:setPixelPivot(0, 0)
    self.p4:setPixelPivot(0, 0)
    self.p5:setPixelPivot(0, 0)
    self.p6:setPixelPivot(0, 0)
    self.p7:setPixelPivot(0, 0)
    self.p8:setPixelPivot(0, 0)
end

function NinePatch:draw(x, y, w, h)
    local a = self.a
    local b = self.b
    local c = self.c
    local d = self.d
    local e = self.e
    local f = self.f
    local sb = (w - a - c) / b
    local se = (h - d - f) / e
    self.p0:draw(x,         y,         0, 1,  1)
    self.p1:draw(x + a,     y,         0, sb, 1)
    self.p2:draw(x + w - c, y,         0, 1,  1)
    self.p3:draw(x,         y + d,     0, 1,  se)
    self.p4:draw(x + a,     y + d,     0, sb, se)
    self.p5:draw(x + w - c, y + d,     0, 1,  se)
    self.p6:draw(x,         y + h - f, 0, 1,  1)
    self.p7:draw(x + a,     y + h - f, 0, sb, 1)
    self.p8:draw(x + w - c, y + h - f, 0, 1,  1)
end

return NinePatch
