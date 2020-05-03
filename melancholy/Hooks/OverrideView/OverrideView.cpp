#include "OverrideView.h"

void __fastcall OverrideView::Hook(void *pClientMode, int edx, CViewSetup *pViewSetup)
{
	VMTManager &hook = VMTManager::GetHook(pClientMode);
	hook.GetMethod<void(__thiscall *)(void *, CViewSetup *)>(Index)(pClientMode, pViewSetup);

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (!pLocal)
		return;

	if (gESP.NoZoom) {
		pViewSetup->fov = gESP.CustomFOV;
		pLocal->SetFov(gESP.CustomFOV);
	}

	else
	{
		if (!pLocal->IsScoped()) {
			pViewSetup->fov = gESP.CustomFOV;
			pLocal->SetFov(gESP.CustomFOV);
		}
	}
}