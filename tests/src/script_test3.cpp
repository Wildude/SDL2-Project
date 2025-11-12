// script processing test 3
// Reading lua variables from external .lua files
#include <iostream>

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Load script
    if (luaL_dofile(L, "../Files/scripts/script.lua") != LUA_OK) {
        std::cerr << "Lua Error: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    // Get global string: playerName
    lua_getglobal(L, "playerName");
    if (lua_isstring(L, -1)) {
        const char* name = lua_tostring(L, -1);
        std::cout << "Player Name: " << name << std::endl;
    } else {
        std::cout << "playerName is not a string!\n";
    }
    lua_pop(L, 1);  // remove value from stack

    // Get global number: health
    lua_getglobal(L, "health");
    if (lua_isnumber(L, -1)) {
        int hp = (int)lua_tonumber(L, -1);
        std::cout << "Health: " << hp << std::endl;
    } else {
        std::cout << "health is not a number!\n";
    }
    lua_pop(L, 1);

    lua_close(L);
    return 0;
}
