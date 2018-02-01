#include <unordered_map>
#include <iostream>

#include "ctx.h"
#include "luautils.h"
#include "event.h"
#include "xpatche.h"

static std::unordered_map<std::string,std::unordered_map<xxPlugin*,int> > xvEventListenning;

static int xxlListen(lua_State *L)
{
    static const char *fn="listen";
    if(xxCheckType(L,fn,1,LUA_TSTRING)==tMismatch) return 0;
    if(xxCheckType(L,fn,2,LUA_TFUNCTION)==tMismatch) return 0;
    lua_settop(L,2);
    int ref = lua_ref(L,true);
    if(xxListen(xxGetPluginByLState(L),std::string(lua_tostring(L,1)),ref) == false)
        xxError(L,"The same listenner have already been set!");

    return 0;
}

static int xxlListenStop(lua_State *L)
{
    static const char *fn="listen_stop";
    if(xxCheckType(L,fn,1,LUA_TSTRING)==tMismatch) return 0;
    xxListenStop(xxGetPluginByLState(L),std::string(lua_tostring(L,1)));
    return 0;
}

void xxInitEnvEvent(lua_State *L)
{
    lua_pushcfunction(L,xxlListen);
    lua_setfield(L,-2,"listen");
    lua_pushcfunction(L,xxlListenStop);
    lua_setfield(L,-2,"listen_stop");
}

bool xxListen(xxPlugin *plg,const std::string &event,int ref)
{
    if(xvEventListenning.count(event) == 0)
        xvEventListenning.insert(std::make_pair(event,std::move(std::unordered_map<xxPlugin*,int>())));
    auto &lst = xvEventListenning[event];
    if(lst.count(plg) != 0)
        return false;
    lst.insert(std::make_pair(plg,ref));
    plg->listenning.insert(event);
    return true;
}

void xxListenStop(xxPlugin *plg,const std::string &event)
{
    auto &lst = xvEventListenning[event];
    if(plg->listenning.count(event) != 0)
    {
        auto iter = lst.find(plg);
        lua_unref(plg->lua,iter->second);
        lst.erase(iter);
        plg->listenning.erase(plg->listenning.find(event));
    }
    std::cout << "AFTRE"<<lst.size()<<std::endl;
}

void xxListenStopAll(xxPlugin *plg)
{
    // TODO: Check if there's any performance issue.
    for(auto &event : plg->listenning)
    {
        xxListenStop(plg,event);
    }
}

bool xpEvent(const char *event)
{
    bool ret = false;
    auto lst = xvEventListenning[event];
    if(lst.size() == 0) return false;
    for(const auto &pa : lst)
    {
        lua_State *L = pa.first->lua;
        xxSafeCallStart(L);
        lua_getref(L,pa.second);
        xxSafeCallEnd(L,0,1);
        if(ret == false && lua_gettop(L) >= 1 && lua_toboolean(L,1)) ret = true;
    }
    return ret;
}
