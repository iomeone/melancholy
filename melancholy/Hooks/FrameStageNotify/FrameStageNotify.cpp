#include "FrameStageNotify.h"

using fn = void(__thiscall *)(PVOID, ClientFrameStage_t);

//TODO: find a better method (https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/game/client/c_baseplayer.h#L392-L393) ?
void ThirdpersonDrawFix(CBaseEntity *pLocal)
{
	static DWORD offset = (gNetVars.get_offset("DT_BaseEntity", "moveparent") - 0xC); //- 12 to get at 0x1B0

	if (!pLocal->IsAlive() || pLocal->GetClassNum() != TF2_Sniper || !gESP.Thirdperson)
		return;

	CBaseCombatWeapon *pLocalWeapon = pLocal->GetActiveWeapon();

	if (!pLocalWeapon)
		return;

	if (pLocal->IsScoped())
	{
		pLocal->RemoveEffect(EF_NODRAW);
		pLocalWeapon->RemoveEffect(EF_NODRAW);

		CBaseEntity *attachment = gInts.EntityList->GetClientEntity(*reinterpret_cast<int*>((pLocal + offset)) & 0xFFF);
		int count = 0;

		while (attachment && count++ < 32) 
		{
			if (attachment->GetClassId() == CTFWearable)
				attachment->RemoveEffect(EF_NODRAW);

			attachment = gInts.EntityList->GetClientEntity(*reinterpret_cast<int *>((attachment + (offset + 0x4))) & 0xFFF);
		}
	}
}

void __fastcall FrameStageNotify::Hook(PVOID client, int edx, ClientFrameStage_t frame)
{
	VMTManager &hk = VMTManager::GetHook(client);

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (!pLocal)
		return;

	gGlow.Run(pLocal, frame);

	static Vec3 *pPunchAng	= nullptr;
	static Vec3 *pPunchVel	= nullptr;
	static Vec3 vecPunchAng = Vec3();
	static Vec3 vecPunchVel = Vec3();

	if (frame == FRAME_RENDER_START)
	{
		ThirdpersonDrawFix(pLocal);

		if (pLocal->IsAlive())
		{
			pPunchAng = reinterpret_cast<Vec3 *>(pLocal + 0xE8C);
			pPunchVel = reinterpret_cast<Vec3 *>(pLocal + 0xEC8);

			if (pPunchAng && pPunchVel)
			{
				vecPunchAng = *pPunchAng;
				vecPunchVel = *pPunchVel;

				pPunchAng->Set();
				pPunchVel->Set();
			}
		}
	}

	hk.GetMethod<fn>(Index)(client, frame);

	if (pPunchAng && pPunchVel) {
		*pPunchAng = vecPunchAng;
		*pPunchVel = vecPunchVel;
	}
}