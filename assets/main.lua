require("strict.lua")
require("camera.lua")

local MenuState = require("menu_state.lua")
local GameState = require("game_state.lua")

local state

function changeGlobalState(target)
    local stateBuilder = {
        menu = function () return MenuState() end,
        game = function () return GameState() end
    }
    state = stateBuilder[target]()
end

function haru.init()
    changeGlobalState("menu")
end

function haru.shutdown()
end

function haru.update(deltaTime)
    state:update(deltaTime)
end

function haru.draw()
    state:draw()
end
