local Object = require("classic.lua")

local NinePatch = Object:extend()

function NinePatch:new(texture, left, bottom, right, top)
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

function NinePatch:draw(x0, y0, x1, y1)
    local a = self.a
    local b = self.b
    local c = self.c
    local d = self.d
    local e = self.e
    local f = self.f
    local sb = (x1 - x0 - a - c) / b
    local se = (y1 - y0 - d - f) / e
    self.p0:draw(x0,     y0,     0, 1,  1)
    self.p1:draw(x0 + a, y0,     0, sb, 1)
    self.p2:draw(x1 - c, y0,     0, 1,  1)
    self.p3:draw(x0,     y0 + d, 0, 1,  se)
    self.p4:draw(x0 + a, y0 + d, 0, sb, se)
    self.p5:draw(x1 - c, y0 + d, 0, 1,  se)
    self.p6:draw(x0,     y1 - f, 0, 1,  1)
    self.p7:draw(x0 + a, y1 - f, 0, sb, 1)
    self.p8:draw(x1 - c, y1 - f, 0, 1,  1)
end

return NinePatch
