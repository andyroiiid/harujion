local Object = require("classic.lua")

local Player = require("flappy/player.lua")
local Pipes = require("flappy/pipes.lua")
local SFX = require("flappy/sfx.lua")

local Flappy = Object:extend()

local font = haru.SpriteFont.new("monogram.png")
local backgroundTexture = haru.Texture.load("flappy/background-day.png")
local messageTexture = haru.Texture.load("flappy/message.png")

local KEY_SPACE = 32

function Flappy:new()
    haru.window.setTitle("Flappy")
    camera:setHalfHeight(160)
    haru.renderer.setClearColor(78 / 255, 192 / 255, 202 / 255)
    self.background = haru.Sprite.new(backgroundTexture)
    self.message = haru.Sprite.new(messageTexture)
    self:reset()
end

function Flappy:reset()
    self.player = Player()
    self.pipes = Pipes()
    self.waiting = true
    haru.mouse.setCursor(true)
    self.prevOpening = false
    self.scores = 0
end

function Flappy:update(deltaTime)
    -- handle input
    if haru.keyboard.justPressed(KEY_SPACE) or haru.mouse.justPressed(0) then
        if self.waiting then
            haru.audio.fireOneShotEvent(SFX.SWOOSH)
            self.waiting = false
            haru.mouse.setCursor(false)
        else
            haru.audio.fireOneShotEvent(SFX.WING)
            self.player:jump()
        end
    end

    if self.waiting then
        return
    end

    -- update game objects
    self.pipes:update(deltaTime)
    self.player:update(deltaTime)

    -- check falling death
    if self.player.y <= -192 then
        haru.audio.fireOneShotEvent(SFX.DIE)
        self:reset()
    end

    -- check passing openings
    local opening = self.pipes:getCurrentOpening()
    if opening then
        if self.player.y <= opening - 64 or self.player.y >= opening + 64 then
            -- player hit pipes
            haru.audio.fireOneShotEvent(SFX.HIT)
            self:reset()
        else
            self.prevOpening = true
        end
    else
        if self.prevOpening then
            -- just passed an opening
            haru.audio.fireOneShotEvent(SFX.POINT)
            self.scores = self.scores + 1
        end
        self.prevOpening = false
    end

    -- slightly move camera
    camera:setCenter(0.0, self.player.y * 0.2)
end

function Flappy:draw()
    self.background:draw(288, 0)
    self.background:draw(0, 0)
    self.background:draw(-288, 0)

    if self.waiting then
        self.message:draw(0, 0)
    else
        self.pipes:draw()
        self.player:draw()

        -- draw mouse position, just for testing
        local mouseX, mouseY = camera:getMousePosition()
        haru.renderer.setDrawColor(1.0, 1.0, 1.0)
        haru.renderer.drawPoint(mouseX, mouseY, 10.0)

        font:draw(-32, self.player.y + 32, "Scores=" .. self.scores)
    end
end

return Flappy
