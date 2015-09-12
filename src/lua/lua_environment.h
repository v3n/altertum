/* 
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <lua.hpp>

namespace altertum
{

struct LuaEnvironment
{

LuaEnvironment();
~LuaEnvironment();

void execute_string(const char* s);
void load_libraries();

private:
    lua_State * _l;
};

} // namespace altertum
