#include "ShouldDrawViewmodel.h"

bool __fastcall ShouldDrawViewmodel::Hook(void *pClientMode, int edx)
{
	VMTManager &hook = VMTManager::GetHook(pClientMode);

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (pLocal && pLocal->IsScoped() && gESP.NoScope && gESP.NoZoom)
		return true;

	return hook.GetMethod<bool(__fastcall *)()>(Index)();
}