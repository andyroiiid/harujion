local Object = require("classic.lua")

local VBox = require("ui/vbox.lua")
local Button = require("ui/button.lua")

local MenuState = Object:extend()

function MenuState:new()
    local vbox = VBox(0.5, 0, 1, 1, 32, 32, -32, -32, 32)
    vbox:addChild(Button.fullRect("attack", function() print("attack") end))
    vbox:addChild(Button.fullRect("defend", function() print("defend") end))
    vbox:addChild(Button.fullRect("skill", function() print("skill") end))
    vbox:addChild(Button.fullRect("to game", function() changeGlobalState("game") end))
    self.vbox = vbox
end

function MenuState:update(deltaTime)
    camera:update(4, 3) -- just fake a map ratio
    self.vbox:updateLayout(camera:hudBounds())
    local mouseX, mouseY = camera:mouseHudPosition()
    local pressed = haru.mouse.pressed(0)
    self.vbox:handleMouse(mouseX, mouseY, pressed)
end

function MenuState:draw()
    camera:preDrawHud()
    self.vbox:draw()
end

return MenuState
