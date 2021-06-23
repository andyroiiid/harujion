require("strict.lua")

local Tileset = require("tileset.lua")

local tileset = Tileset("test_tileset.lua")
local tilemap = require("test_tilemap.lua")

function haru.init()
    haru.renderer.setClearColor(7 / 255, 24 / 255, 33 / 255)
end

function haru.shutdown()
end

function haru.update(deltaTime)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    local mapWidth = tileset.tileWidth * tilemap.width
    local mapHeight = tileset.tileHeight * tilemap.height

    local camWidth, camHeight
    if mapWidth / mapHeight > width / height then
        -- match width
        camWidth = mapWidth
        camHeight = height / width * camWidth
    else
        -- match height
        camHeight = mapHeight
        camWidth = width / height * camHeight
    end
    haru.renderer.setMatrixOrtho(
        (mapWidth - camWidth) / 2,
        (mapWidth + camWidth) / 2,
        (mapHeight - camHeight) / 2,
        (mapHeight + camHeight) / 2
    )

    for i, layer in ipairs(tilemap.layers) do
        for y = 0, layer.height - 1 do
            local y_ = tilemap.height - 1 - y
            for x = 0, layer.width - 1 do
                local tileIdx = layer.data[x + y * layer.width + 1]
                if tileIdx ~= 0 then
                    tileset:draw(tileIdx, x * tileset.tileWidth, y_ * tileset.tileHeight)
                end
            end
        end
    end
end
