#ifndef XPATCHE_INC
#define XPATCHE_INC 
#ifdef __cplusplus
extern "C"
{
#endif

int xpGetVersion();
const char *xpGetVersionString();
bool xpCheckCompatibility(const char *version,const char *build);

int xpRegisterPlugin(const char *main_script);
void xpUnloadPlugin(const char *id);
#define XP_SUCCEED 0
#define XP_APIVER_UNSUPPORTED 1
#define XP_ERR_LOADING_SCRIPT 2
#define XP_ERR_EXECUTING_SCRIPT 3
#define XP_PLUGIN_INFO_ERR 4
#define XP_IDENTIFIER_ALREADY_EXISTS 5
#define XP_INITIALIZE_FAILED 6

void xpEvent(const char *event);

#ifdef __cplusplus
}
#endif
#endif