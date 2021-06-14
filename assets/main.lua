require("player.lua")
require("pipes.lua")

function haru.init()
    haru.window.setTitle("Flappy Bird")
    haru.renderer.setCameraHalfHeight(5.0)

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
        player:jump()
    end
    prevPressed = pressed

    pipes:update(deltaTime)
    player:update(deltaTime)

    if player.y <= -5.0  or player.y >= 5.0 then
        reset()
    end

    local opening = pipes:getCurrentOpening()
    if opening then
        if player.y <= opening - 2.0 or player.y >= opening + 2.0 then
            reset()
        else
            prevOpening = true
        end
    else
        if prevOpening then
            scores = scores + 1
        end
        prevOpening = false
    end

    haru.window.setTitle("scores = " .. scores)
end

function haru.draw()
    pipes:draw()
    player:draw();
end
