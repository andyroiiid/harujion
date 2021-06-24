local Object = require("classic.lua")

local Tilemap = Object:extend()

function Tilemap:new(path, tileset)
    local tilemap = require(path)
    self.width = tilemap.width
    self.height = tilemap.height
    self.layers = tilemap.layers
    self.tileset = tileset
end

function Tilemap:getMapSize()
    local tileset = self.tileset
    return tileset.tileWidth * self.width, tileset.tileHeight * self.height
end

function Tilemap:drawLayer(idx)
    local tileset = self.tileset
    local tileWidth = tileset.tileWidth
    local tileHeight = tileset.tileHeight
    local layer = self.layers[idx]
    for y = 1, self.height do
        for x = 1, self.width do
            local tileIdx = layer[y][x]
            if tileIdx ~= 0 then
                tileset:draw(tileIdx, (x - 1) * tileWidth, (y - 1) * tileHeight)
            end
        end
    end
end

function Tilemap:draw()
    for i = 1, #self.layers do
        self:drawLayer(i)
    end
end

return Tilemap
