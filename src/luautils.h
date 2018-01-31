#pragma once
#include <luajit-2.0/lua.hpp>

inline static void xxError(lua_State *L,const char *msg)
{
    lua_pushstring(L,msg);
    lua_error(L);
}

int xxSafeCallErrorCallback(lua_State *L);
enum xxCheckTypeRet
{
    tMatch=1,tOptional=2,tMismatch=0,
};
xxCheckTypeRet xxCheckType(lua_State *L,const char *funcname,int argindex,int expected,bool optional = false);

inline static void xxSafeCallStart(lua_State *L)
{
    lua_pushcfunction(L,xxSafeCallErrorCallback);
}

inline static int xxSafeCallEnd(lua_State *L,int nargs,int nresults)
{
    return lua_pcall(L,nargs,nresults,-(nargs+2));
}

