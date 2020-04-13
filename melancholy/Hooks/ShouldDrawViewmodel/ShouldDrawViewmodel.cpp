#include "ShouldDrawViewmodel.h"

bool __fastcall ShouldDrawViewmodel::Hook(void *pClientMode, int edx)
{
	VMTManager &hook = VMTManager::GetHook(pClientMode);

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (pLocal == nullptr)
		return false;

	if (gESP.Active && gESP.NoScope && gESP.NoZoom) {
		if (pLocal->IsScoped())
			return true;

		return hook.GetMethod<bool(__fastcall *)()>(Index)();
	}

	return hook.GetMethod<bool(__fastcall *)()>(Index)();
}