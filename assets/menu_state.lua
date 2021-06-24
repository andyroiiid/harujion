local Object = require("classic.lua")

local HBox = require("ui/hbox.lua")
local VBox = require("ui/vbox.lua")
local Text = require("ui/text.lua")
local Button = require("ui/button.lua")

local MenuState = Object:extend()

function MenuState:new()
    local ui = HBox(0, 0, 1, 1, 32, 32, -32, -32, 32)

    local leftColumn = VBox(0, 0, 1, 1, 0, 0, 0, 0)
    leftColumn:addChild(Text.fullRect("Test RPG Game"))
    leftColumn:addChild(Text.fullRect("Made by andyroiiid"))
    leftColumn:addChild(Text.fullRect("Powered by harujion"))
    ui:addChild(leftColumn)

    local rightColumn = VBox(0, 0, 1, 1, 0, 0, 0, 0, 32)
    rightColumn:addChild(Button.fullRect("start", function() changeGlobalState("game") end))
    rightColumn:addChild(Button.fullRect("quit", function() haru.window.close() end))
    ui:addChild(rightColumn)

    self.ui = ui
end

function MenuState:update(deltaTime)
    camera:update(4, 3) -- just fake a map ratio
    self.ui:updateLayout(camera:hudBounds())
    local mouseX, mouseY = camera:mouseHudPosition()
    local pressed = haru.mouse.pressed(0)
    self.ui:handleMouse(mouseX, mouseY, pressed)
end

function MenuState:draw()
    camera:preDrawHud()
    self.ui:draw()
end

return MenuState
