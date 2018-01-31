#include "version.h"
#include "xpatche.h"

int xpGetVersion()
{
    return xxVersion;
}

const char *xpGetVersionString()
{
    return xxVersionString;
}

bool xpCheckCompatibility(const char *version,const char *build)
{
    // TODO: Check compatibility to IINA
    return true;
}
