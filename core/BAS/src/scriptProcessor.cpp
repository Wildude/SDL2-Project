#include <scriptProcessor.hpp>
#include <fstream>
extern "C" {
    // #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}
std::ofstream fs("../Files/Data/script.log");
script::~script(){
    fs << "Closing lua state\n";
    lua_close(L);
    fs << "Script ended";
    fs.close();
}
script::script()
{
    fs << "Script log created\n";
    L = luaL_newstate();
    fs << "Creating new state\n";
    if(!L)fs << "Failed to create Lua state\n";
    fs << "New state created\n";   
    luaL_openlibs(L);
    fs << "Libraries loaded\n";
}
script::script(const char* scriptpath) : script() // constructor delegation
{
    fs << "Loading script: \"" << scriptpath << "\"\n";
    if(luaL_loadfile(L, scriptpath) != LUA_OK)
    {
        fs << "[Lua err]: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message
    }
    else {
        fs << "Script (\" " << scriptpath << "\") loaded\n";
        checkRunStatus();
    }
}
// function checks the run status of scripts after load
// also runs lua functions with nargs = number of arguments and nresults = number of returns
bool script::checkRunStatus(int nargs , int nresults , int errfunc ){
    fs << "Checking run status:";
    int runStatus = lua_pcall(L, nargs, nresults, errfunc);
    if(runStatus != LUA_OK){
        fs << "\n[Lua rerr]: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1); // remove error message;
        return false;
    }
    fs << " Run status good\n";
    return true;
}
// dumps the whole lua stack
void script::dumpLuaStack() {
    fs << "Dumping lua stack:";
    int top = lua_gettop(L);
    if(top < 1){
        fs << "{}\n";
        return;
    }
    else fs << "\n{\n";
    fs << " Lua Stack (top -> bottom):\n {\n";
    for (int i = top; i >= 1; --i) {
        int t = lua_type(L, i);
        fs << "   [" << i << "] " << lua_typename(L, t) << " | ";

        switch (t) {
            case LUA_TSTRING:
                fs << lua_tostring(L, i);
                break;
            case LUA_TBOOLEAN:
                fs << (lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                fs << lua_tonumber(L, i);
                break;
            case LUA_TTABLE:
                fs << "(table)";
                break;
            case LUA_TFUNCTION:
                fs << "(function)";
                break;
            default:
                fs << "(unprintable)";
        }
        fs << "\n";
    }
    fs << " }\n";
    fs << "}\n";
}
// gets lua global variables and returns their value if they are the same type as inputted
int script::getglobalA(const char* globalvar){
    return lua_getglobal(L, globalvar);
}
const char* script::getglobal(const char* globalvar, const char* type )
{
    fs << "Getting global variable: \"" << globalvar << "\":";
    lua_getglobal(L, globalvar);
    if(!strcmp(type, "string"))
    {
        if(lua_isstring(L, -1)){
            fs << " success\n";
            const char* name = lua_tostring(L, -1);
            lua_pop(L, 1);
            return name;
        }
        else 
        {
            fs << "[Lua exc]: \"" << globalvar << "\" is not a string!\n";
            lua_pop(L, 1);
            return NULL;
        }
    }
    else if(!strcmp(type, "number"))
    {
        if(lua_isnumber(L, -1)){
            fs << " success\n";
            const char* name = lua_tostring(L, -1);
            lua_pop(L, 1);
            return name;
        }
        else
        {
            fs << "[Lua exc]: \"" << globalvar << "\" is not a number!\n";
            lua_pop(L, 1);
            return NULL;
        }
    }
    else if(!strcmp(type, "boolean"))
    {
        if(lua_isboolean(L, -1)){
            fs << " success\n";
            const char* name = (lua_toboolean(L, -1) ? "true" : "false");
            lua_pop(L, 1);
            return name;
        }
        else
        {
            fs << "[Lua exc]: \"" << globalvar << "\" is not a boolean!\n";
            lua_pop(L, 1);
            return NULL;
        }
    }
    /*
    else if(!strcmp(type, "table"))
    {
        if(lua_istable(L, -1))
            return (T)lua_topointer(L, -1);
        else
            fs << "[Lua exc]: \"" << globalvar << "\" is not a table!\n";
    }
    else if(!strcmp(type, "function"))
    {
        if(lua_isfunction(L, -1))
            return (T)lua_topointer(L, -1);
        else
            fs << "[Lua exc]: \"" << globalvar << "\" is not a function!\n";
    }
    else if(!strcmp(type, "userdata"))
    {
        if(lua_isuserdata(L, -1))
            return (T)lua_touserdata(L, -1);
        else
            fs << "[Lua exc]: \"" << globalvar << "\" is not a userdata!\n";
    }
    */
    else if(!strcmp(type, "nil"))
    {
        if(lua_isnil(L, -1))
        {
            lua_pop(L, 1);
            return "isnil";
        }
        else
        {
            fs << "[Lua exc]: \"" << globalvar << "\" is not nil!\n";
            lua_pop(L, 1);
            return NULL;
        }
            
    }
    else
    {
        fs << "[Lua exc]: Unknown type \"" << type << "\" requested for \"" << globalvar << "\"\n";
        lua_pop(L, 1);
        return NULL;
    }
}
// gets global function and puts it into the lua stack (if the function exists)
bool script::getglobalFunc(const char* funcname){
    fs << "Getting global function: \"" << funcname << "\":";
    lua_getglobal(L, funcname);
    if(lua_isfunction(L, -1))
    {
        fs << " success\n";
        return true;
    }
    else
    {
        fs << "\n[Lua exc]: \"" << funcname << "\" is not a function!\n";
        return false;
    }
}
// pushes a number into the lua stack
void script::pushnum(int num){
    lua_pushnumber(L, num);
}
// pushes as string into the lua stack
void script::pushstr(const char* str){
    lua_pushstring(L, str);
}
// pushes a boolean into the lua stack
void script::pushbool(int tof){
    lua_pushboolean(L, tof);
}
// creates a lua table and pushes it into the stack
void script::newtab(){
    lua_newtable(L);
}
// sets field for the table in the lua stack
void script::setfield(const char* field, int index ){
    lua_setfield(L, index, field);
    // remember that when setting field the value at the top of stack is popped.
}
// gets an array element at index -> index and returns the type of the element
int script::getEi(int index, int stacki ){
    lua_rawgeti(L, stacki, index);
}
// gets field from the table in the lua stack
int script::getfield(const char* field, int index ){
    return lua_getfield(L, index, field);
}
// gets the number of elements in the lua stack
int script::gettop(){
    lua_gettop(L);
}
// gets the element in ith index in the lua stack and returns it as string
const char* script::tostr(int index ){
    return lua_tostring(L, index);
}
// gets the element in ith index in the lua stack and returns it as number
int script::tonum(int index ){
    return lua_tonumber(L, index);
}
// gets the element in ith index in the lua stack and returns it as boolean
bool script::tobool(int index ){
    return lua_toboolean(L, index);
}
// pops 'nums' elements off the lua stack
void script::pop(int nums ){
    fs << "Popping stack: "<< nums << "x:";
    if(gettop() < 1){
        fs << " Stack already empty\n";
        return;
    }
    lua_pop(L, nums);
    fs << " Success\n";
}
// gets the datatype of the element at 'index' position of the lua stack
const char* script::gettype(int index ){
    if(!gettop()){
        return "empty stack";
    }
    fs << "Getting type of stack[" << index << "]:";
    int t = lua_type(L, index);
    switch (t) {
        case LUA_TSTRING:
        {
            const char* str = "string";
            fs << ' ' << str << std::endl;
            return str;
        }
        case LUA_TBOOLEAN:
        {
            const char* str = "boolean";
            fs << ' ' << str << std::endl;
            return str;
        }
        case LUA_TNUMBER:
        {
            const char* str = "number";
            fs << ' ' << str << std::endl;
            return str;
        }
        case LUA_TTABLE:
        {
            const char* str = "table";
            fs << ' ' << str << std::endl;
            return str;
        }
        case LUA_TFUNCTION:
        {
            const char* str = "function";
            fs << ' ' << str << std::endl;
            return str;
        }
        default:
        {
            const char* str = "unprintable";
            fs << ' ' << str << std::endl;
            return str;
        }
    }
}
