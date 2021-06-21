local Object = require("classic.lua")

local Camera = Object:extend()

function Camera:new()
    self.halfHeight = 100
    self.halfWidth = 100
    self.x = 0
    self.y = 0
end

function Camera:update()
    local width, height = haru.window.getFramebufferSize()
    self.halfWidth = width / height * self.halfHeight
end

function Camera:preDraw()
    haru.renderer.setMatrixOrtho(
        self.x - self.halfWidth,
        self.x + self.halfWidth,
        self.y - self.halfHeight,
        self.y + self.halfHeight
    )
end

function Camera:setHalfHeight(halfHeight)
    self.halfHeight = halfHeight
end

function Camera:setCenter(x, y)
    self.x = x
    self.y = y
end

function Camera:getMousePosition()
    local x, y = haru.mouse.normalizedPosition()
    x = x * 2 - 1
    y = y * 2 - 1
    return self.x + x * self.halfWidth, self.y + y * self.halfHeight
end

camera = Camera()
