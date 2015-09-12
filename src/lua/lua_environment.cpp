/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#include <cstring>

#include "macros.h"
#include "lua_environment.h"

namespace altertum
{

/* from taylor001/crown:lua_environment.cpp:50 */
// When an error occurs, logs the error message and pauses the engine.
static int error_handler(lua_State* L)
{
    lua_getfield(L, LUA_GLOBALSINDEX, "debug");
    if (!lua_istable(L, -1))
    {
        lua_pop(L, 1);
        return 0;
    }

    lua_getfield(L, -1, "traceback");
    if (!lua_isfunction(L, -1))
    {
        lua_pop(L, 2);
        return 0;
    }

    lua_pushvalue(L, 1); // Pass error message
    lua_pushinteger(L, 2);
    lua_call(L, 2, 1); // Call debug.traceback

    printf(lua_tostring(L, -1)); // Print error message
    lua_pop(L, 1); // Remove error message from stack
    lua_pop(L, 1); // Remove debug.traceback from stack

    // device()->pause();
    return 0;
}

LuaEnvironment::LuaEnvironment()
{
    _l = luaL_newstate();

    ASSERT(_l);
}

LuaEnvironment::~LuaEnvironment()
{
    lua_close(_l);
}

void LuaEnvironment::execute_string(const char* s)
{
    lua_pushcfunction(_l, error_handler);
    luaL_loadstring(_l, s);
    lua_pcall(_l, 0, 0, -2);
    lua_pop(_l, 1);
}

void LuaEnvironment::load_libraries()
{
    luaL_openlibs(_l);
}

} // namespace altertum
