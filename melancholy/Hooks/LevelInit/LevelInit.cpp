#include "LevelInit.h"

using fn_pre		= void(__thiscall *)(void *, char const *);
using fn_post		= void(__thiscall *)(void *);
using fn_shutdown	= void(__thiscall *)(void *);

void __fastcall LevelInit::LevelInitPreEntity(void *chl_client, int edx, char const *pMapName) {
	VMTManager &hk = VMTManager::GetHook(chl_client);
	hk.GetMethod<fn_pre>(PreIndex)(chl_client, pMapName);
	gLocalInfo.LevelInitialized = false;
}

void __fastcall LevelInit::LevelInitPostEntity(void *chl_client, int edx) {
	VMTManager &hk = VMTManager::GetHook(chl_client);
	hk.GetMethod<fn_post>(PostIndex)(chl_client);
	gLocalInfo.LevelInitialized = true;
}

void __fastcall LevelInit::LevelShutdown(void *chl_client, int edx) {
	VMTManager &hk = VMTManager::GetHook(chl_client);
	hk.GetMethod<fn_shutdown>(ShutdownIndex)(chl_client);
	gLocalInfo.LevelInitialized = false;
}