#include "Hooks/Hooks.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	gInts.Initialize();
	gNetVars.Initialize();
	gHooks.Initialize();
	gMatHelper.Initialize();

	//TODO: have all the used convars in one place and initialize them there
	if (!gMisc.cheats)
		gMisc.cheats = gInts.ConVars->FindVar("sv_cheats");

	return 0x0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), nullptr, 0x0, nullptr);

	return TRUE;
}