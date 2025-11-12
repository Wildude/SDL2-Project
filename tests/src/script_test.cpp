// script processing test
#include <iostream>

extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}

int main() {
    lua_State* L = luaL_newstate();      // Create new Lua state
    luaL_openlibs(L);                    // Load standard Lua libraries

    if (luaL_dostring(L, "print('Hello from Lua!')")) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);                        // Close Lua state
    return 0;
}
