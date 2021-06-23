local Object = require("classic.lua")

local Tileset = Object:extend()

function Tileset:new(path)
    local tileset = require(path)
    local tilesetTexture = haru.Texture.load(tileset.image)
    local textureWidth, textureHeight = tilesetTexture:getSize()

    local tileWidth = tileset.tilewidth
    local tileHeight = tileset.tileheight
    local spacing = tileset.spacing
    self.tileWidth = tileWidth
    self.tileHeight = tileHeight

    local columns = (textureWidth + spacing) / (tileWidth + spacing)
    local rows = (textureHeight + spacing) / (tileHeight + spacing)

    self.tiles = {}
    for i = 0, tileset.tilecount - 1, 1 do
        local ix = i % columns
        local iy = rows - 1 - math.floor(i / columns)
        local sprite = haru.Sprite.new(tilesetTexture)
        sprite:setPixelRect(ix * (tileWidth + spacing), iy * (tileHeight + spacing), tileWidth, tileHeight)
        sprite:setPixelPivot(0, 0)
        table.insert(self.tiles, sprite)
    end
end

function Tileset:draw(idx, x, y)
    self.tiles[idx]:draw(x, y, 0, 1.0001, 1.0001) -- fill the gaps between tiles (due to non-integer coordinates)
end

return Tileset
