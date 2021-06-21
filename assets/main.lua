local texture = haru.Texture.load("blue.png")
local sprite = haru.Sprite.new(texture)

function haru.init()
end

function haru.shutdown()
end

function haru.update(deltaTime)
end

function haru.draw()
    local width, height = haru.window.getFramebufferSize()
    haru.renderer.setMatrixOrtho(0, width, 0, height)
    sprite:draw(width / 2, height / 2)
end
