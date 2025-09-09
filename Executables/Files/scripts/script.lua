print("Script loaded at runtime!")

function slowPrint()
    for i = 5, 1, -1 do
        print("Countdown: " .. i)
        coroutine.yield() -- pause and return to C++
    end
    print("Go!")
end

co = coroutine.create(slowPrint)


if player == nil then
    player = {
        name = "Firaol",
        health = 100,
        position = { x = 50, y = 60 }
    }
end

print("Lua script loaded!")

playerName = "Firaol"
health = 100

function damagePlayer(amount)
    health = health - amount
    print("Player damaged by " .. amount .. ". Health now: " .. health)
end

printPlayerName(playerName)  -- This calls C++ function now!

-- Call new C++ function with player table
processPlayer(player)


-- Call C++ damagePlayer, get returned new health
local newHealth = damagePlayerLua(player, 15)
print("Health after damage (from Lua): " .. newHealth)