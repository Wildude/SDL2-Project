// script processing test 8
// Hot-Reloading lua scripts (without restarting/recompiling the program)
#include <iostream>
#include <string>

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}
// C++ function to be called from Lua
int cpp_printPlayerName(lua_State* L) {
    // Check argument count (expecting 1 string)
    if (!lua_isstring(L, 1)) {
        lua_pushstring(L, "Expected a string argument");
        lua_error(L);
        return 0; // won't be reached, lua_error long jumps
    }
    const char* name = lua_tostring(L, 1);
    std::cout << "C++ says: Player name is " << name << std::endl;

    return 0;  // number of return values to Lua
}
// a function that processes lua table
int processPlayer(lua_State* L) {
    // Expect 1 argument: a table at stack index 1
    if (!lua_istable(L, 1)) {
        lua_pushstring(L, "Expected a table argument");
        lua_error(L);
        return 0;
    }

    // Get player.name
    lua_getfield(L, 1, "name");  // pushes value of player["name"]
    const char* name = lua_tostring(L, -1);
    lua_pop(L, 1);

    // Get player.health
    lua_getfield(L, 1, "health");
    int health = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    // Get player.position table
    lua_getfield(L, 1, "position");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_pushstring(L, "player.position must be a table");
        lua_error(L);
        return 0;
    }

    // Get position.x
    lua_getfield(L, -1, "x");
    int x = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    // Get position.y
    lua_getfield(L, -1, "y");
    int y = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    lua_pop(L, 1);  // pop position table

    std::cout << "Process Player:\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Position: (" << x << ", " << y << ")\n";

    return 0;
}
// a function that reduces player health
int cpp_damagePlayer(lua_State* L) {
    // Expect 2 args: player table (index 1), damage amount (index 2)
    if (!lua_istable(L, 1)) {
        lua_pushstring(L, "First argument must be a player table");
        lua_error(L);
        return 0;
    }
    if (!lua_isnumber(L, 2)) {
        lua_pushstring(L, "Second argument must be a number");
        lua_error(L);
        return 0;
    }

    // Get current health
    lua_getfield(L, 1, "health");
    int health = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);

    int damage = (int)lua_tonumber(L, 2);

    int newHealth = health - damage;

    // Set new health back in the table
    lua_pushnumber(L, newHealth);
    lua_setfield(L, 1, "health");

    // Return new health to Lua
    lua_pushnumber(L, newHealth);
    return 1;  // number of return values
}

void register_cpp_functions(lua_State* L) {
    lua_register(L, "printPlayerName", cpp_printPlayerName);
    lua_register(L, "processPlayer", processPlayer);
    lua_register(L, "damagePlayerLua", cpp_damagePlayer);
}

void run_script(lua_State* L, const char* path) {
    if (luaL_dofile(L, path) != LUA_OK) {
        std::cerr << "[Lua Error] " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message
    }
}

int main() {
    const char* script_path = "../Files/scripts/script.lua";

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    register_cpp_functions(L);

    std::cout << "Initial script load...\n";
    run_script(L, script_path);

    std::string input;
    while (true) {
        std::cout << "\nType 'reload' to reload script or 'exit' to quit:\n> ";
        std::getline(std::cin, input);

        if (input == "exit") break;
        else if (input == "reload") {
            std::cout << "Reloading script...\n";
            run_script(L, script_path);
        }
    }
    std::cout << "> Running completed\n";
    lua_close(L);
    return 0;
}
