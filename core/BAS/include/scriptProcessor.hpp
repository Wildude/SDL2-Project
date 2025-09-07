#pragma once
#include <fstream>
#include <cstring>
extern "C" {
    #include "lua/lua.h"
    //#include "lua/lauxlib.h"
    //#include "lua/lualib.h"
}
// std::ofstream fs("../Files/Data/script.log");
class script
{
    public:
        ~script();
        script();
        script(const char* scriptpath);
        // function checks the run status of scripts after load
        // also runs lua functions with nargs = number of arguments and nresults = number of returns
        bool checkRunStatus(int nargs = 0, int nresults = 0, int errfunc = 0);
        // dumps the whole lua stack
        void dumpLuaStack();
        // gets lua global variables and returns their value if they are the same type as inputted
        int getglobalA(const char* globalvar);
        const char* getglobal(const char* globalvar, const char* type = "string");
        // gets global function and puts it into the lua stack (if the function exists)
        bool getglobalFunc(const char* funcname);
        // pushes a number into the lua stack
        void pushnum(int num);
        // pushes as string into the lua stack
        void pushstr(const char* str);
        // pushes a boolean into the lua stack
        void pushbool(int tof);
        // creates a lua table and pushes it into the stack
        void newtab();
        // sets field for the table in the lua stack
        void setfield(const char* field, int index = -1);
        // gets an array element at index -> index and returns the type of the element
        int getEi(int index, int stacki = -1);
        // gets field from the table in the lua stack
        int getfield(const char* field, int index = -1);
        // gets the number of elements in the lua stack
        int gettop();
        // gets the element in ith index in the lua stack and returns it as string
        const char* tostr(int index = -1);
        // gets the element in ith index in the lua stack and returns it as number
        int tonum(int index = -1);
        // gets the element in ith index in the lua stack and returns it as boolean
        bool tobool(int index = -1);
        // pops 'nums' elements off the lua stack
        void pop(int nums = 1);
        // gets the datatype of the element at 'index' position of the lua stack
        const char* gettype(int index = -1);
        /*
        template <class T>
        T getglobalT(const char* globalvar)
        {
            lua_getglobal(L, globalvar);
            if (constexpr(is_same_v<T, int>)) {
                if (!lua_isnumber(L, -1)) { 
                    fs << "[Lua exec]: \"" << globalvar << "\" is not a  number";
                }
                int val = (int)lua_tonumber(L, -1);
                lua_pop(L, 1);
                return val;
            } 
            else if (constexpr (is_same_v<T, double>)) {
            if (!lua_isnumber(L, -1)) { 
                    fs << "[Lua exec]: \"" << globalvar << "\" is not a  number";
                }
                double val = (double)lua_tonumber(L, -1);
                lua_pop(L, 1);
                return val;
            } 
            else if (constexpr (is_same_v<T, float>)){
            if (!lua_isnumber(L, -1)) { 
                    fs << "[Lua exec]: \"" << globalvar << "\" is not a  number";
                }
                float val = (float)lua_tonumber(L, -1);
                lua_pop(L, 1);
                return val;
            } 
            else if (constexpr (is_same_v<T, bool>)){
                if (!lua_isboolean(L, -1)) { 
                    fs << "[Lua exec]: \"" << globalvar << "\" is not a  boolean";
                }
                bool val = lua_toboolean(L, -1);
                lua_pop(L, 1);
                return val;
            } 
            else if (constexpr (is_same_v<T, string>)){
                if (!lua_isstring(L, -1)) { 
                    fs << "[Lua exec]: \"" << globalvar << "\" is not a string";
                }
                string val = lua_tostring(L, -1);
                lua_pop(L, 1);
                return val;
            }
            else {
                lua_pop(L, 1);
                fs << "[Lua exec]: Unsupported type requested from Lua\n";
                return NULL;
            }
        }
        */
    private:
        lua_State* L;
};