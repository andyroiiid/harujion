local Object = require("classic.lua")

local Pipes = Object:extend()

local function generateOpening()
    return math.random() * 5.0 - 2.5
end

function Pipes:new()
    self.sprite = haru.Sprite.new("flappy/pipe-green.png", 32)
    self.sprite:setPixelPivot(26.0, 320.0)
    self.xs = {10.0, 20.0, 30.0}
    self.ys = {generateOpening(), generateOpening(), generateOpening()}
end

function Pipes:update(deltaTime)
    for i, x in ipairs(self.xs) do
        x = x - 5.0 * deltaTime
        if x < -10.0 then
            -- reuse old array item instead of inserting & deleting
            if i == 1 then
                self.xs[i] = self.xs[3] + 10.0
            else
                self.xs[i] = self.xs[i - 1] + 10.0
            end
            self.ys[i] = generateOpening()
        else
            self.xs[i] = x
        end
    end
end

function Pipes:getCurrentOpening()
    for i, x in ipairs(self.xs) do
        if x > -0.8125 and x < 0.8125 then
            return self.ys[i]
        end
    end
    return nil
end

function Pipes:draw()
    for i, x in ipairs(self.xs) do
        local y = self.ys[i]
        self.sprite:setFlip(false, false)
        self.sprite:draw(x, -2.0 + y, 0.0)
        self.sprite:setFlip(true, false)
        self.sprite:draw(x, 2.0 + y, math.pi)
    end
end

return Pipes