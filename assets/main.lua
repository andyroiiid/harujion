require("strict.lua")

local Button = require("button.lua")

local leftButton = Button(0, 0, 0.5, 1, 32, 32, -96, -32)
leftButton.text = "left"
leftButton.onPressed = function() print("left is clicked") end

local rightButton = Button(0.5, 0, 1, 1, 96, 32, -32, -32)
rightButton.text = "right"
rightButton.onPressed = function() print("right is clicked") end

local button = Button(0.5, 0.5, 0.5, 0.5, -64, -32, 64, 32)
button.text = "test"
button.onPressed = function() print("test is clicked") end

function haru.init()
    haru.renderer.setClearColor(0.0, 0.0, 0.0)
end

function haru.shutdown()
end

function haru.update(deltaTime)
    local width, height = haru.window.getFramebufferSize()
    leftButton:updateLayout(0, 0, width, height)
    rightButton:updateLayout(0, 0, width, height)
    button:updateLayout(0, 0, width, height)
    local normalizedX, normalizedY = haru.mouse.normalizedPosition()
    local mouseX, mouseY = normalizedX * width, normalizedY * height
    local pressed = haru.mouse.pressed(0)
    leftButton:handleMouse(mouseX, mouseY, pressed)
    rightButton:handleMouse(mouseX, mouseY, pressed)
    button:handleMouse(mouseX, mouseY, pressed)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    haru.renderer.setMatrixOrtho(0, width, 0, height)
    leftButton:draw()
    rightButton:draw()
    button:draw()
end
