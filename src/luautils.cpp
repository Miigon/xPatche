#include <iostream>

#include "luautils.h"

xxCheckTypeRet xxCheckType(lua_State *L,const char *funcname,int argindex,int expected,bool optional)
{
    static const char *tlist[] = 
    {
        "no value","nil","boolean","lightuserdata","number","string","table","function","userdata","thread",
    };
    int type = lua_type(L,argindex);
    if(type == expected) return tMatch;
    if((type == LUA_TNONE || type == LUA_TNIL) && optional) return tOptional;
    static char buf[256];
    sprintf(buf,"bad argument #%i to `%s` (%s expected, got %s)",argindex,funcname,tlist[expected+1],tlist[type+1]);
    xxError(L,buf);
    return tMismatch;
}

int xxSafeCallErrorCallback(lua_State *L)
{
    std::cerr << "ERR: "<<lua_tostring(L,-1)<<std::endl;
    return 0;
}
