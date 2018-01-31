#pragma once
#include <unordered_set>
#include <string>

#include "luautils.h"

struct xxPlugin
{
    lua_State *lua;
    std::unordered_set<std::string> listenning;
};

xxPlugin *xxGetPluginByID(const std::string &id);
xxPlugin *xxGetPluginByLState(lua_State *L);
void xxUnloadPlugin(const std::string &id);