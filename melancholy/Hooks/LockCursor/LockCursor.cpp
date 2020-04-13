#include "LockCursor.h"

using fn = void(__fastcall *)();

void __fastcall LockCursor::Hook(void *surface, int edx)
{
	VMTManager &hk = VMTManager::GetHook(surface);
	hk.GetMethod<fn>(Index)();

	if (gMenu.bOpen)
		gInts.Surface->UnlockCursor();

	else hk.GetMethod<fn>(Index)();
}