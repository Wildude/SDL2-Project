// script processing test 5
// calling C++ functions from lua
#include <iostream>

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
int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    // Register cpp_printPlayerName as "printPlayerName" in Lua
    lua_register(L, "printPlayerName", cpp_printPlayerName);
    const char* script_path = "../Files/scripts/script.lua";

    if (luaL_dofile(L, script_path) != LUA_OK) {
        std::cerr << "Lua Error: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    lua_close(L);
    return 0;
}