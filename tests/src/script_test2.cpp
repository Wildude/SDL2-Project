// script processing test 2
// testing external scripts
#include <iostream>

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "../Files/scripts/script.lua") != LUA_OK) {
        std::cerr << "Lua Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message from stack
    } else {
        std::cout << "Lua script loaded successfully.\n";
    }

    lua_close(L);
    return 0;
}
