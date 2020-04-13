#include "SceneEnd.h"

using fn = void(__thiscall *)(void *, int);

void __fastcall SceneEnd::Hook(void *render_view, int edx)
{
	VMTManager &hk = VMTManager::GetHook(gInts.RenderView);

	gChams.Run();

	hk.GetMethod<fn>(Index);
}