#include "xpatche.h"
#include "utilityapi.h"
#include "luautils.h"

void (^xcAlert)(const char *,unsigned int);

int xxlAlert(lua_State *L)
{
    if(xxCheckType(L,"alert",1,LUA_TSTRING) == tMismatch) return 0;
    auto arg2 = xxCheckType(L,"alert",2,LUA_TNUMBER,true);
    const char *msg = lua_tostring(L,1);
    int style;
    if(arg2 == tMismatch) return 0;
    else if(arg2 == tOptional) style = 1;
    else style = lua_tonumber(L,2);
    xcAlert(msg,style);
    return 0;
}

void xxInitEnvUtility(lua_State *L)
{
    lua_pushcfunction(L,xxlAlert);
    lua_setfield(L,-2,"alert");
}
