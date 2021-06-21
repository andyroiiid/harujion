local Object = require("classic.lua")

local Pipes = Object:extend()

local texture = haru.Texture.load("flappy/pipe-green.png")

local function generateOpening()
    return math.random() * 160 - 80
end

function Pipes:new()
    self.sprite = haru.Sprite.new(texture)
    self.sprite:setPixelPivot(26, 320)
    self.xs = {320, 640, 960}
    self.ys = {generateOpening(), generateOpening(), generateOpening()}
end

function Pipes:update(deltaTime)
    for i, x in ipairs(self.xs) do
        x = x - 160 * deltaTime
        if x < -320 then
            -- reuse old array item instead of inserting & deleting
            if i == 1 then
                self.xs[i] = self.xs[3] + 320
            else
                self.xs[i] = self.xs[i - 1] + 320
            end
            self.ys[i] = generateOpening()
        else
            self.xs[i] = x
        end
    end
end

function Pipes:getCurrentOpening()
    for i, x in ipairs(self.xs) do
        if x > -26 and x < 26 then
            return self.ys[i]
        end
    end
    return nil
end

function Pipes:draw()
    for i, x in ipairs(self.xs) do
        local y = self.ys[i]
        self.sprite:setFlip(false, false)
        self.sprite:draw(x, y - 64)
        self.sprite:setFlip(true, false)
        self.sprite:draw(x, y + 64, math.pi)
    end
end

return Pipes
