local vec2 = {}

function vec2.rotate(x, y, angle)
    local c = math.cos(angle)
    local s = math.sin(angle)
    return c * x - s * y, s * x + c * y
end

function vec2.normalize(x, y)
    if x == 0 and y == 0 then
        return 0, 0
    end
    local length = math.sqrt(x * x + y * y)
    return x / length, y / length
end

return vec2
