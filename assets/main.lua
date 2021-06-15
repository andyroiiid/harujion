local Player = require("player.lua")
local Pipes = require("pipes.lua")

local background = haru.Sprite.new("background-day.png", 32)
local message = haru.Sprite.new("message.png", 32)

local soundEvents = {
    die = haru.audio.getEventDescription("event:/die"),
    hit = haru.audio.getEventDescription("event:/hit"),
    point = haru.audio.getEventDescription("event:/point"),
    swoosh = haru.audio.getEventDescription("event:/swoosh"),
    wing = haru.audio.getEventDescription("event:/wing")
}

local player = Player()
local pipes = Pipes()
local waiting = true
local prevOpening = false
local scores = 0

local function reset()
    waiting = true
    prevOpening = false
    scores = 0

    pipes:reset()
    player:reset()
end

function haru.init()
    haru.window.setTitle("Flappy Bird")
    haru.renderer.setClearColor(78.0 / 255.0, 192.0 / 255.0, 202.0 / 255.0)
    haru.camera.setHalfHeight(5.0)
    reset()
end

function haru.shutdown()
end

function haru.update(deltaTime)
    if haru.input.keyJustPressed(32) or haru.input.mouseButtonJustPressed(0) then
        if waiting then
            haru.audio.fireOneShotEvent(soundEvents.swoosh)
            waiting = false
        else
            haru.audio.fireOneShotEvent(soundEvents.wing)
            player:jump()
        end
    end

    if waiting then
        return
    end

    pipes:update(deltaTime)
    player:update(deltaTime)

    if player.y <= -6.0 then
        haru.audio.fireOneShotEvent(soundEvents.die)
        reset()
    end

    local opening = pipes:getCurrentOpening()
    if opening then
        if player.y <= opening - 2.0 or player.y >= opening + 2.0 then
            haru.audio.fireOneShotEvent(soundEvents.hit)
            reset()
        else
            prevOpening = true
        end
    else
        if prevOpening then
            haru.audio.fireOneShotEvent(soundEvents.point)
            scores = scores + 1
            haru.window.setTitle("scores = " .. scores)
        end
        prevOpening = false
    end

    haru.camera.setCenter(0.0, player.y * 0.2)
end

function haru.draw()
    background:draw(9.0, 0.0, 0.0)
    background:draw(0.0, 0.0, 0.0)
    background:draw(-9.0, 0.0, 0.0)

    if waiting then
        message:draw(0.0, 0.0, 0.0)
    else
        pipes:draw()
        player:draw()
    end

    local mouseX, mouseY = haru.input.mouseWorldPosition()
    haru.renderer.drawPoint(mouseX, mouseY, 10.0)
end
