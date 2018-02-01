#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <cstdio>

#include "xpatche.h"
#include "version.h"
#include "ctx.h"
#include "event.h"
#include "luautils.h"
#include "utilityapi.h"
#include "playbackapi.h"

static std::unordered_map<lua_State*,xxPlugin*> xvStateKey; // lua_State*:plugin
static std::unordered_map<std::string,xxPlugin*> xvLoaded; // identifier:plugin

static void xxInitEnv(lua_State *L)
{
    luaL_openlibs(L);

    lua_newtable(L);
    xxInitEnvEvent(L);
    xxInitEnvUtility(L);
    xxInitEnvPlayback(L);

    lua_setglobal(L,"xp");
}

int xpRegisterPlugin(const char *main_script)
{
    lua_State *L = lua_open();
    
    // Load script and plugin info
    xxSafeCallStart(L);
    if(luaL_loadfile(L,main_script) != 0) return XP_ERR_LOADING_SCRIPT;
    const char *id_c = nullptr;
    if(xxSafeCallEnd(L,0,1) == 0)
    {
        lua_getfield(L,-1,"api_ver");
        if(lua_type(L,-1) != LUA_TNUMBER) return XP_PLUGIN_INFO_ERR;
        if(lua_tonumber(L,-1) != xxLuaApiVersion) return XP_APIVER_UNSUPPORTED;
        lua_pop(L,1);

        lua_getfield(L,-1,"identifier");
        if(lua_type(L,-1) != LUA_TSTRING) return XP_PLUGIN_INFO_ERR;
        id_c = lua_tostring(L,-1);
        lua_pop(L,1);
    }
    else return XP_ERR_EXECUTING_SCRIPT;
    // Initialize xPatche & standard lua library
    xxInitEnv(L);

    xxPlugin *plg = new xxPlugin();
    plg->lua = L;
    xvStateKey.insert(std::make_pair(L,plg));
    xvLoaded.insert(std::make_pair(id_c,plg));

    // Call `_G.Initialize`
    xxSafeCallStart(L);
    lua_getglobal(L,"initialize");
    if(xxSafeCallEnd(L,0,1) != 0) return XP_INITIALIZE_FAILED;
    if(lua_type(L,-1) != LUA_TBOOLEAN || lua_toboolean(L,-1) != true)
    {
        xpUnloadPlugin(id_c);
        return XP_INITIALIZE_FAILED;
    }
    return XP_SUCCEED;
}

xxPlugin *xxGetPluginByID(const std::string &id)
{
    return xvLoaded[id];
}

xxPlugin *xxGetPluginByLState(lua_State *L)
{
    return xvStateKey[L];
}

void xpUnloadPlugin(const char *id)
{
    xxUnloadPlugin(id);
}

void xxUnloadPlugin(const std::string &id)
{
    auto plg = xvLoaded[id];
    xxListenStopAll(plg);
    lua_close(plg->lua);
    xvStateKey.erase(plg->lua);
    xvLoaded.erase(id);
    delete plg;
}
