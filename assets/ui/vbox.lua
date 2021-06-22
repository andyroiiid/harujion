local BoxLayout = require("ui/box_layout.lua")

local VBox = BoxLayout:extend()

function VBox:updateLayout(x0, y0, x1, y1)
    x0, y0, x1, y1 = self.rect:layout(x0, y0, x1, y1)
    local nChildren = #self.children
    local dh = (y1 - y0 + self.spacing) / nChildren
    local h = dh - self.spacing
    for i, v in ipairs(self.children) do
        local iy = nChildren + 1 - i
        local y = y0 + (iy - 1) * dh
        v:updateLayout(x0, y, x1, y + h)
    end
end

return VBox
