local BoxLayout = require("box_layout.lua")

local HBox = BoxLayout:extend()

function HBox:updateLayout(x0, y0, x1, y1)
    x0, y0, x1, y1 = self.rect:layout(x0, y0, x1, y1)
    local nChildren = #self.children
    local dw = (x1 - x0 + self.spacing) / nChildren
    local w = dw - self.spacing
    for i, v in ipairs(self.children) do
        local x = x0 + (i - 1) * dw
        v:updateLayout(x, y0, x + w, y1)
    end
end

return HBox
