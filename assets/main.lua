require("strict.lua")
require("camera.lua")

local Tileset = require("tileset.lua")

local HBox = require("ui/hbox.lua")
local Button = require("ui/button.lua")

local tileset = Tileset("gameboy.png", 16, 16, 1, 136)
local tilemap = require("testmap.lua")

local hud = HBox(0, 0, 1, 0, 32, 32, -32, 96, 32)
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
    local mapWidth = tileset.tileWidth * tilemap.width
    local mapHeight = tileset.tileHeight * tilemap.height
    camera:update(mapWidth, mapHeight)

    hud:updateLayout(camera:hudBounds())

    local mouseX, mouseY = camera:mouseHudPosition()
    local pressed = haru.mouse.pressed(0)
    hud:handleMouse(mouseX, mouseY, pressed)
end

function haru.draw()
    camera:preDrawWorld()

    for i, layer in ipairs(tilemap.layers) do
        for y = 1, tilemap.height do
            for x = 1, tilemap.width do
                local tileIdx = layer[y][x]
                if tileIdx ~= 0 then
                    tileset:draw(tileIdx, (x - 1) * tileset.tileWidth, (y - 1) * tileset.tileHeight)
                end
            end
        end
    end

    camera:preDrawHud()

    hud:draw()
end
