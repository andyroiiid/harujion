local Player = require("player.lua")
local Pipes = require("pipes.lua")

function haru.init()
    haru.window.setTitle("Flappy Bird")
    haru.renderer.setCameraHalfHeight(5.0)

    background = haru.renderer.Sprite.new("background-day.png", 32)

    soundEvents = {
        die = haru.audio.getEventDescription("event:/die"),
        hit = haru.audio.getEventDescription("event:/hit"),
        point = haru.audio.getEventDescription("event:/point"),
        swoosh = haru.audio.getEventDescription("event:/swoosh"),
        wing = haru.audio.getEventDescription("event:/wing")
    }

    player = Player()
    pipes = Pipes()

    reset()
end

function haru.shutdown()
end

function reset()
    prevPressed = false
    prevOpening = false
    scores = 0

    pipes:reset()
    player:reset()
end

function haru.update(deltaTime)
    local pressed = haru.window.isKeyPressed(32)
    if pressed and not prevPressed then
        haru.audio.fireOneShotEvent(soundEvents.wing)
        player:jump()
    end
    prevPressed = pressed

    pipes:update(deltaTime)
    player:update(deltaTime)

    if player.y <= -5.0 then
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
        end
        prevOpening = false
    end

    haru.window.setTitle("scores = " .. scores)
end

function haru.draw()
    background:draw(9.0, 0.0, 0.0)
    background:draw(0.0, 0.0, 0.0)
    background:draw(-9.0, 0.0, 0.0)
    pipes:draw()
    player:draw();
end
