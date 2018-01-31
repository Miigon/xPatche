#pragma once
#include "ctx.h"

void xxInitEnvEvent(lua_State *L);
bool xxListen(xxPlugin *plg,const std::string &event,int ref);
void xxListenStop(xxPlugin *plg,const std::string &event);
void xxListenStopAll(xxPlugin *plg);
