-- script template for testing script class
player = "Firaol"
health = 98
alive = true
full_stats = {
    playerName = player,
    playerHealth = health,
    playerState = alive
}
function killPlayer(playerStats)
    print "killing player"
    playerStats.playerHealth = 0
    playerState = false
    return playerStats
end
