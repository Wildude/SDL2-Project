extern "C" {
    #include "lua/lua.h"
    #include "lua/lauxlib.h"
    #include "lua/lualib.h"
}
ofstream fs("../Files/Data/script.log");
class script
{
    public:
        ~script(){
            fs << "Closing lua state\n";
            lua_close(L);
            fs << "Script ended";
            fs.close();
        }
        script()
        {
            fs << "Script log created\n";
            L = luaL_newstate();
            fs << "Creating new state\n";
            if(!L)fs << "Failed to create Lua state\n";
            fs << "New state created\n";   
            luaL_openlibs(L);
            fs << "Libraries loaded\n";
        }
        script(const char* scriptpath) : script() // constructor delegation
        {
            fs << "Loading script: \"" << scriptpath << "\"\n";
            if(luaL_loadfile(L, scriptpath) != LUA_OK)
            {
                fs << "[Lua err]: " << lua_tostring(L, -1) << endl;
                lua_pop(L, 1); // remove error message
            }
            else {
                fs << "Script (\" " << scriptpath << "\") loaded\n";
                checkRunStatus();
            }
        }
        // function checks the run status of scripts after load
        // also runs lua functions with nargs = number of arguments and nresults = number of returns
        bool checkRunStatus(int nargs = 0, int nresults = 0, int errfunc = 0){
            fs << "Checking run status:";
            int runStatus = lua_pcall(L, nargs, nresults, errfunc);
            if(runStatus != LUA_OK){
                fs << "\n[Lua rerr]: " << lua_tostring(L, -1) << endl;
                lua_pop(L, 1); // remove error message;
                return false;
            }
            fs << " Run status good\n";
            return true;
        }
        // dumps the whole lua stack
        void dumpLuaStack() {
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
        int getglobalA(const char* globalvar){
            return lua_getglobal(L, globalvar);
        }
        const char* getglobal(const char* globalvar, const char* type = "string")
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
        bool getglobalFunc(const char* funcname){
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
        void pushnum(int num){
            lua_pushnumber(L, num);
        }
        // pushes as string into the lua stack
        void pushstr(const char* str){
            lua_pushstring(L, str);
        }
        // pushes a boolean into the lua stack
        void pushbool(int tof){
            lua_pushboolean(L, tof);
        }
        // creates a lua table and pushes it into the stack
        void newtab(){
            lua_newtable(L);
        }
        // sets field for the table in the lua stack
        void setfield(const char* field, int index = -1){
            lua_setfield(L, index, field);
            // remember that when setting field the value at the top of stack is popped.
        }
        // gets an array element at index -> index and returns the type of the element
        int getEi(int index, int stacki = -1){
            lua_rawgeti(L, stacki, index);
        }
        // gets field from the table in the lua stack
        int getfield(const char* field, int index = -1){
            return lua_getfield(L, index, field);
        }
        // gets the number of elements in the lua stack
        int gettop(){
            lua_gettop(L);
        }
        // gets the element in ith index in the lua stack and returns it as string
        const char* tostr(int index = -1){
            return lua_tostring(L, index);
        }
        // gets the element in ith index in the lua stack and returns it as number
        int tonum(int index = -1){
            return lua_tonumber(L, index);
        }
        // gets the element in ith index in the lua stack and returns it as boolean
        bool tobool(int index = -1){
            return lua_toboolean(L, index);
        }
        // pops 'nums' elements off the lua stack
        void pop(int nums = 1){
            fs << "Popping stack: "<< nums << "x:";
            if(gettop() < 1){
                fs << " Stack already empty\n";
                return;
            }
            lua_pop(L, nums);
            fs << " Success\n";
        }
        // gets the datatype of the element at 'index' position of the lua stack
        const char* gettype(int index = -1){
            if(!gettop()){
                return "empty stack";
            }
            fs << "Getting type of stack[" << index << "]:";
            int t = lua_type(L, index);
            switch (t) {
                case LUA_TSTRING:
                {
                    const char* str = "string";
                    fs << ' ' << str << endl;
                    return str;
                }
                case LUA_TBOOLEAN:
                {
                    const char* str = "boolean";
                    fs << ' ' << str << endl;
                    return str;
                }
                case LUA_TNUMBER:
                {
                    const char* str = "number";
                    fs << ' ' << str << endl;
                    return str;
                }
                case LUA_TTABLE:
                {
                    const char* str = "table";
                    fs << ' ' << str << endl;
                    return str;
                }
                case LUA_TFUNCTION:
                {
                    const char* str = "function";
                    fs << ' ' << str << endl;
                    return str;
                }
                default:
                {
                    const char* str = "unprintable";
                    fs << ' ' << str << endl;
                    return str;
                }
            }
        }
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