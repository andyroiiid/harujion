Object = require("classic.lua")

Pipes = Object:extend()

function getRandomOpeningHeight()
    return math.random() * 5.0 - 2.5
end

function Pipes:new()
    self.sprite = haru.renderer.Sprite.new("pipe-green.png", 32)
    self:reset()
end

function Pipes:reset()
    self.xs = {
        10.0,
        20.0,
        30.0,
        40.0
    }
    self.ys = {
        getRandomOpeningHeight(),
        getRandomOpeningHeight(),
        getRandomOpeningHeight(),
        getRandomOpeningHeight()
    }
end

function Pipes:update(deltaTime)
    for i, x in ipairs(self.xs) do
        x = x - 5.0 * deltaTime
        if x < -10.0 then
            if i == 1 then
                self.xs[i] = self.xs[#self.xs] + 10.0
            else
                self.xs[i] = self.xs[i - 1] + 10.0
            end
            self.ys[i] = getRandomOpeningHeight()
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
        self.sprite:draw(x, -7.0 + y, 0.0)
        self.sprite:setFlip(true, false)
        self.sprite:draw(x, 7.0 + y, math.pi)
    end
end

pipes = Pipes()
