local Object = require("classic.lua")

local Tileset = require("tilemap/tileset.lua")
local Tilemap = require("tilemap/tilemap.lua")

local VBox = require("ui/vbox.lua")
local Button = require("ui/button.lua")

local tileset = Tileset("tilemap/gameboy.png", 16, 16, 1, 136)
local tilemap = Tilemap("tilemap/testmap.lua", tileset)

local hud = VBox(0.75, 0, 1, 1, 16, 16, -16, -16, 16)
hud:addChild(Button.fullRect("attack", function() print("attack") end))
hud:addChild(Button.fullRect("defend", function() print("defend") end))
hud:addChild(Button.fullRect("skill", function() print("skill") end))
hud:addChild(Button.fullRect("to menu", function() changeGlobalState("menu") end))

local GameState = Object:extend()

function GameState:new()
end

function GameState:update(deltaTime)
    camera:update(tilemap:getMapSize())
    hud:updateLayout(camera:hudBounds())
    local mouseX, mouseY = camera:mouseHudPosition()
    local pressed = haru.mouse.pressed(0)
    hud:handleMouse(mouseX, mouseY, pressed)
end

function GameState:draw()
    camera:preDrawWorld()
    tilemap:draw()
    camera:preDrawHud()
    hud:draw()
end

return GameState
