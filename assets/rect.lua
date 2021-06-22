local Object = require("classic.lua")

local Rect = Object:extend()

function Rect:new(aMinX, aMinY, aMaxX, aMaxY, left, bottom, right, top)
    self.aMinX = aMinX
    self.aMinY = aMinY
    self.aMaxX = aMaxX
    self.aMaxY = aMaxY
    self.left = 0
    self.bottom = 0
    self.right = 0
    self.top = 0
end

function Rect:setPadding(left, bottom, right, top)
    self.left = left
    self.bottom = bottom
    self.right = right
    self.top = top
end

local function lerp(a, b, t)
    return a * (1.0 - t) + b * t
end

function Rect:layout(left, bottom, right, top)
    local x0 = lerp(left,   right,  self.aMinX) + self.left
    local y0 = lerp(bottom, top,    self.aMinY) + self.bottom
    local x1 = lerp(left,   right,  self.aMaxX) + self.right
    local y1 = lerp(bottom, top,    self.aMaxY) + self.top
    return x0, y0, x1, y1
end

return Rect
