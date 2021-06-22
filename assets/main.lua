require("strict.lua")

function haru.init()
    haru.renderer.setClearColor(0.0, 0.0, 0.0)
end

function haru.shutdown()
end

function haru.update(deltaTime)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    haru.renderer.setMatrixOrtho(0, width, 0, height)
end
