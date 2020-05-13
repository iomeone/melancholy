#include "DrawModelExecute.h"

using fn = void(__thiscall *)(CModelRender *, const DrawModelState_t &, const ModelRenderInfo_t &, matrix3x4 *);

void __stdcall DrawModelExecute::Hook(const DrawModelState_t &state, const ModelRenderInfo_t &info, matrix3x4 *matrix)
{
	//VMTManager &hk = VMTManager::GetHook(gInts.ModelRender);
	//fn original = hk.GetMethod<fn>(Index);

	//CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	//if (pLocal)
	//{
	//	CBaseEntity *ent = gInts.EntityList->GetClientEntity(info.entity_index);

	//	if (gChams.Active)
	//	{
	//		if (ent)
	//		{
	//			if (ent->IsPlayer() && ent != pLocal)
	//			{
	//				if (gChams.PlayerChams && (gChams.NoTeammatePlayers ? ent->GetTeamNum() != pLocal->GetTeamNum() : true)) {
	//					return;
	//				}
	//			}

	//			else if (ent->IsBuilding())
	//			{
	//				if (gChams.BuildingChams && (gChams.NoTeammateBuildings ? ent->GetTeamNum() != pLocal->GetTeamNum() : true)) {
	//					return;
	//				}
	//			}

	//			else if (ent->IsPickup())
	//			{
	//				if (gChams.PickupChams) {
	//					return;
	//				}
	//			}

	//			else if (ent->GetClassId() == CTFWearable)
	//			{
	//				CBaseEntity *owner = gInts.EntityList->GetClientEntityFromHandle(ent->GetOwner());

	//				if (!owner || owner == pLocal)
	//					original(gInts.ModelRender, state, info, matrix);

	//				if (gChams.PlayerChams && (gChams.NoTeammatePlayers ? owner->GetTeamNum() != pLocal->GetTeamNum() : true) && gChams.PlayerCosmetics) {
	//					return;
	//				}
	//			}
	//		}
	//	}
	//}

	//original(gInts.ModelRender, state, info, matrix);
}