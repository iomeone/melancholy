#include "OnScreenSizeChanged.h"
#include "../../Modules/ESP/ESP.h"

using fn = void(__thiscall *)(void *, int, int);

void __fastcall OnScreenSizeChanged::Hook(void *surface, int edx, int nOldWidth, int nOldHeight) {
	VMTManager &hk = VMTManager::GetHook(surface);
	hk.GetMethod<fn>(Index)(surface, nOldWidth, nOldHeight);

	gScreenSize.Update();
	gESP.ReloadFonts();
}