// script processing test 4
// calling lua functions from C++
#include <iostream>

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Load script from your specified path
    const char* script_path = "../Files/scripts/script.lua";

    if (luaL_dofile(L, script_path) != LUA_OK) {
        std::cerr << "Lua Error: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    // Access and print playerName from Lua
    lua_getglobal(L, "playerName");
    if (lua_isstring(L, -1)) {
        const char* name = lua_tostring(L, -1);
        std::cout << "Player Name: " << name << std::endl;
    }
    lua_pop(L, 1);

    // Access and print health from Lua
    lua_getglobal(L, "health");
    if (lua_isnumber(L, -1)) {
        int hp = (int)lua_tonumber(L, -1);
        std::cout << "Health: " << hp << std::endl;
    }
    lua_pop(L, 1);

    // Call Lua function damagePlayer(30)
    lua_getglobal(L, "damagePlayer");
    if (lua_isfunction(L, -1)) {
        lua_pushnumber(L, 30);        // Push argument
        if (lua_pcall(L, 1, 0, 0) != LUA_OK) {  // 1 arg, 0 results
            std::cerr << "Error calling damagePlayer: " << lua_tostring(L, -1) << std::endl;
            lua_pop(L, 1);  // remove error message
        }
    } else {
        std::cerr << "damagePlayer function not found!\n";
        lua_pop(L, 1); // pop non-function value
    }

    // Check updated health after damagePlayer call
    lua_getglobal(L, "health");
    if (lua_isnumber(L, -1)) {
        int hp = (int)lua_tonumber(L, -1);
        std::cout << "Health after damage: " << hp << std::endl;
    }
    lua_pop(L, 1);

    lua_close(L);
    return 0;
}
