local mathf = {}

function mathf.mix(a, b, t)
    return a * (1.0 - t) + b * t
end

return mathf
