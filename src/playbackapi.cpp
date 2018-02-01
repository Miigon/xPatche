#include "playbackapi.h"
#include "luautils.h"

const char *(^xcCurrentURL)();
void (^xcOpenURL)(const char *);

int xxlGetCurrentUrl(lua_State *L)
{
    const char *url = xcCurrentURL();
    if(url != nullptr)
    {
        lua_pushstring(L,url);
        return 1;
    }
    return 0;
}


int xxlOpenMedia(lua_State *L)
{
    if(xxCheckType(L,"open_media",1,LUA_TSTRING) == tMismatch) return 0;
    xcOpenURL(lua_tostring(L,1));
    return 0;
}


void xxInitEnvPlayback(lua_State *L)
{
    lua_pushcfunction(L,xxlGetCurrentUrl);
    lua_setfield(L,-2,"get_current_url");
    lua_pushcfunction(L,xxlOpenMedia);
    lua_setfield(L,-2,"open_media");
}
