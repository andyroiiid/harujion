local Object = require("classic.lua")

local Rect = require("ui/rect.lua")

local BoxLayout = Object:extend()

function BoxLayout:new(aMinX, aMinY, aMaxX, aMaxY, left, bottom, right, top, spacing)
    self.rect = Rect(aMinX, aMinY, aMaxX, aMaxY)
    self.rect:setPadding(left, bottom, right, top)
    self.spacing = spacing or 0
    self.children = {}
end

function BoxLayout:addChild(element)
    table.insert(self.children, element)
end

function BoxLayout:handleMouse(mouseX, mouseY, pressed)
    for i, v in ipairs(self.children) do
        v:handleMouse(mouseX, mouseY, pressed)
    end
end

function BoxLayout:draw()
    for i, v in ipairs(self.children) do
        v:draw()
    end
end

return BoxLayout
