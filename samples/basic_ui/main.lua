require("strict.lua")

local VBox = require("ui/vbox.lua")
local HBox = require("ui/hbox.lua")
local Button = require("ui/button.lua")

local leftVBox = VBox(0, 0, 0.5, 1, 32, 32, -16, -32, 32)
leftVBox:addChild(Button.fullRect("left", function() print("left") end))
leftVBox:addChild(Button.fullRect("right", function() print("right") end))
leftVBox:addChild(Button.fullRect("test", function() print("test") end))
local rightVBox = VBox(0.5, 0, 1, 1, 16, 32, -32, -32, 32)
rightVBox:addChild(Button.fullRect("hello", function() print("hello") end))
local rightDownHBox = HBox(0, 0, 1, 1, 0, 0, 0, 0, 32)
rightDownHBox:addChild(Button.fullRect("goodbye", function() print("goodbye") end))
rightDownHBox:addChild(Button.fullRect("world", function() print("world") end))
rightVBox:addChild(rightDownHBox)

function haru.init()
    haru.renderer.setClearColor(0.0, 0.0, 0.0)
end

function haru.shutdown()
end

function haru.update(deltaTime)
    local width, height = haru.window.getFramebufferSize()
    leftVBox:updateLayout(0, 0, width, height)
    rightVBox:updateLayout(0, 0, width, height)
    local normalizedX, normalizedY = haru.mouse.normalizedPosition()
    local mouseX, mouseY = normalizedX * width, normalizedY * height
    local pressed = haru.mouse.pressed(0)
    leftVBox:handleMouse(mouseX, mouseY, pressed)
    rightVBox:handleMouse(mouseX, mouseY, pressed)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    haru.renderer.setMatrixOrtho(0, width, 0, height)
    leftVBox:draw()
    rightVBox:draw()
end
