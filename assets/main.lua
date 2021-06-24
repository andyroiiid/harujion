require("strict.lua")
require("camera.lua")

local Tileset = require("tileset.lua")
local Tilemap = require("tilemap.lua")

local VBox = require("ui/vbox.lua")
local Button = require("ui/button.lua")

local tileset = Tileset("gameboy.png", 16, 16, 1, 136)
local tilemap = Tilemap("testmap.lua", tileset)

local hud = VBox(0.75, 0, 1, 1, 16, 16, -16, -16, 16)
hud:addChild(Button.fullRect("attack", function() print("attack") end))
hud:addChild(Button.fullRect("defend", function() print("defend") end))
hud:addChild(Button.fullRect("skill", function() print("skill") end))
hud:addChild(Button.fullRect("item", function() print("item") end))

function haru.init()
    haru.renderer.setClearColor(7 / 255, 24 / 255, 33 / 255)
end

function haru.shutdown()
end

function haru.update(deltaTime)
    camera:update(tilemap:getMapSize())
    hud:updateLayout(camera:hudBounds())
    local mouseX, mouseY = camera:mouseHudPosition()
    local pressed = haru.mouse.pressed(0)
    hud:handleMouse(mouseX, mouseY, pressed)
end

function haru.draw()
    camera:preDrawWorld()
    tilemap:draw()
    camera:preDrawHud()
    hud:draw()
end
