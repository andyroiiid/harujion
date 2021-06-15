local Object = require("classic.lua")

local Player = require("flappy/player.lua")
local Pipes = require("flappy/pipes.lua")
local SFX = require("flappy/sfx.lua")

local Flappy = Object:extend()

function Flappy:new()
    haru.camera.setHalfHeight(5.0)
    haru.renderer.setClearColor(78.0 / 255.0, 192.0 / 255.0, 202.0 / 255.0)
    self.background = haru.Sprite.new("flappy/background-day.png", 32)
    self.message = haru.Sprite.new("flappy/message.png", 32)
    self:reset()
end

function Flappy:reset()
    self.player = Player()
    self.pipes = Pipes()
    self.waiting = true
    haru.input.setCursor(true)
    self.prevOpening = false
    self.scores = 0
    haru.window.setTitle("scores = " .. self.scores)
end

function Flappy:update(deltaTime)
    -- handle input
    if haru.input.keyJustPressed(32) or haru.input.mouseButtonJustPressed(0) then
        if self.waiting then
            haru.audio.fireOneShotEvent(SFX.SWOOSH)
            self.waiting = false
            haru.input.setCursor(false)
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
    if self.player.y <= -6.0 then
        haru.audio.fireOneShotEvent(SFX.DIE)
        self:reset()
    end

    -- check passing openings
    local opening = self.pipes:getCurrentOpening()
    if opening then
        if self.player.y <= opening - 2.0 or self.player.y >= opening + 2.0 then
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
            haru.window.setTitle("scores = " .. self.scores)
        end
        self.prevOpening = false
    end

    -- slightly move camera
    haru.camera.setCenter(0.0, self.player.y * 0.2)
end

function Flappy:draw()
    self.background:draw(9.0, 0.0, 0.0)
    self.background:draw(0.0, 0.0, 0.0)
    self.background:draw(-9.0, 0.0, 0.0)

    if self.waiting then
        self.message:draw(0.0, 0.0, 0.0)
    else
        self.pipes:draw()
        self.player:draw()

        -- draw mouse position, just for testing
        local mouseX, mouseY = haru.input.mouseWorldPosition()
        haru.renderer.drawPoint(mouseX, mouseY, 10.0)
    end
end

return Flappy
