local Object = require("classic.lua")

local Camera = Object:extend()

function Camera:new()
    self.screenWidth = 1
    self.screenHeight = 1
    self.mapWidth = 1
    self.mapHeight = 1
    self.camWidth = 1
    self.camHeight = 1
    self.mouseX = 0
    self.mouseY = 0
end

function Camera:update(mapWidth, mapHeight)
    local screenWidth, screenHeight = haru.window.getFramebufferSize()
    self.screenWidth = screenWidth
    self.screenHeight = screenHeight

    self.mapWidth = mapWidth
    self.mapHeight = mapHeight

    local mapRatio = mapWidth / mapHeight
    local screenRatio = screenWidth / screenHeight
    if mapRatio > screenRatio then
        -- match width
        self.camWidth = mapWidth
        self.camHeight = mapWidth / screenRatio
        self.hudWidth = screenWidth
        self.hudHeight = screenWidth / mapRatio
    else
        -- match height
        self.camHeight = mapHeight
        self.camWidth = mapHeight * screenRatio
        self.hudWidth = screenHeight * mapRatio
        self.hudHeight = screenHeight
    end

    self.mouseX, self.mouseY = haru.mouse.normalizedPosition()
end

function Camera:mouseWorldPosition()
    return self.mapWidth * 0.5 + (self.mouseX - 0.5) * self.camWidth,
           self.mapHeight * 0.5 + (self.mouseY - 0.5) * self.camHeight
end

function Camera:preDrawWorld()
    haru.renderer.setMatrixOrtho(
        (self.mapWidth - self.camWidth) / 2,
        (self.mapWidth + self.camWidth) / 2,
        (self.mapHeight - self.camHeight) / 2,
        (self.mapHeight + self.camHeight) / 2
    )
end

function Camera:hudBounds()
    return (self.screenWidth - self.hudWidth) / 2,
           (self.screenHeight - self.hudHeight) / 2,
           (self.screenWidth + self.hudWidth) / 2,
           (self.screenHeight + self.hudHeight) / 2
end

function Camera:mouseHudPosition()
    return self.screenWidth * self.mouseX, self.screenHeight * self.mouseY
end

function Camera:preDrawHud()
    haru.renderer.setMatrixOrtho(0, self.screenWidth, 0, self.screenHeight)
end

camera = Camera()
