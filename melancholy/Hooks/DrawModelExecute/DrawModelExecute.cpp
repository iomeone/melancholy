#include "DrawModelExecute.h"

using fn = void(__thiscall *)(CModelRender *, const DrawModelState_t &, const ModelRenderInfo_t &, matrix3x4 *);

void __stdcall DrawModelExecute::Hook(const DrawModelState_t &state, const ModelRenderInfo_t &info, matrix3x4 *matrix)
{
	//VMTManager &hk = VMTManager::GetHook(gInts.ModelRender);
	//fn original = hk.GetMethod<fn>(Index);

	//auto cham = [&](IMaterial *mat, RGBA_t &col, ChamMode_t mode) -> void
	//{
	//	if (mat)
	//	{
	//		switch (mode)
	//		{
	//			case ChamMode_t::VISIBLE: {
	//				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//				gMatHelper.ForceMaterial(mat, col);
	//				original(gInts.ModelRender, state, info, matrix);
	//				break;
	//			}
	//			
	//			case ChamMode_t::INVISIBLE: {
	//				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	//				gMatHelper.ForceMaterial(mat, col);
	//				original(gInts.ModelRender, state, info, matrix);

	//				gMatHelper.ResetMaterial();
	//				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//				original(gInts.ModelRender, state, info, matrix);
	//				break;
	//			}
	//			
	//			case ChamMode_t::ALWAYS: {
	//				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//				gMatHelper.ForceMaterial(mat, col);
	//				original(gInts.ModelRender, state, info, matrix);

	//				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	//				gMatHelper.ForceMaterial(mat, col);
	//				original(gInts.ModelRender, state, info, matrix);

	//				
	//				break;
	//			}
	//		}

	//		gMatHelper.ResetMaterial();
	//	}	
	//};

	//bool was_chammed		= false;
	//IMaterial *chammed_mat	= nullptr;
	//RGBA_t chammed_col		= RGBA_t();
	//ChamMode_t chammed_mode	= ChamMode_t::DEFAULT;

	//if (gESP.Active)
	//{
	//	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	//	if (pLocal)
	//	{
	//		CBaseEntity *ent = gInts.EntityList->GetClientEntity(info.entity_index);

	//		if (ent && ent != pLocal && !ent->IsDormant() && ent->IsAlive())
	//		{
	//			RGBA_t col = Utils::GetTeamColor(ent->GetTeamNum());

	//			if (ent->IsPlayer())
	//			{
	//				if (gESP.Players && gESP.PlayerChams && (gESP.NoTeammatePlayers ? ent->GetTeamNum() != pLocal->GetTeamNum() : true))
	//				{
	//					IMaterial *player_mat = (gESP.PlayerChams < 2 ? gMatHelper.shaded : gMatHelper.flat);
	//					ChamMode_t player_mode = ChamMode_t::DEFAULT;

	//					switch (gESP.PlayerChamsMode) {
	//						case 0: { player_mode = ChamMode_t::VISIBLE; break;	}
	//						case 1: { player_mode = ChamMode_t::INVISIBLE; break; }
	//						case 2: { player_mode = ChamMode_t::ALWAYS; break; }
	//					}

	//					was_chammed	= true;
	//					chammed_mat	= player_mat;
	//					chammed_col	= col;
	//					chammed_mode = player_mode;
	//				}
	//			}

	//			else if (ent->IsBuilding())
	//			{
	//				if (gESP.Buildings && gESP.BuildingChams && (gESP.NoTeammateBuildings ? ent->GetTeamNum() != pLocal->GetTeamNum() : true))
	//				{
	//					IMaterial *building_mat = (gESP.BuildingChams < 2 ? gMatHelper.shaded : gMatHelper.flat);
	//					ChamMode_t building_mode = ChamMode_t::DEFAULT;

	//					switch (gESP.BuildingChamsMode) {
	//						case 0: { building_mode = ChamMode_t::VISIBLE; break; }
	//						case 1: { building_mode = ChamMode_t::INVISIBLE; break; }
	//						case 2: { building_mode = ChamMode_t::ALWAYS; break; }
	//					}

	//					was_chammed = true;
	//					chammed_mat = building_mat;
	//					chammed_col = col;
	//					chammed_mode = building_mode;
	//				}
	//			}

	//			else if (ent->IsPickup())
	//			{
	//				if (gESP.Pickups && gESP.PickupChams)
	//				{
	//					IMaterial *pickup_mat	= (gESP.PickupChams < 2 ? gMatHelper.shaded : gMatHelper.flat);
	//					ChamMode_t pickup_mode	= ChamMode_t::DEFAULT;

	//					switch (gESP.PickupChamsMode) {
	//						case 0: { pickup_mode = ChamMode_t::VISIBLE; break;	}
	//						case 1: { pickup_mode = ChamMode_t::INVISIBLE; break; }
	//						case 2: { pickup_mode = ChamMode_t::ALWAYS; break; }
	//					}

	//					was_chammed	= true;
	//					chammed_mat	= pickup_mat;
	//					chammed_col	= Utils::GetPickupColor(ent);
	//					chammed_mode = pickup_mode;
	//				}
	//			}

	//			else if (ent->IsBaseCombatWeapon())
	//			{
	//				CBaseEntity *owner = gInts.EntityList->GetClientEntityFromHandle(ent->GetOwner());

	//				if (owner && owner != pLocal)
	//				{
	//					if (gESP.Players && gESP.PlayerChams && (gESP.NoTeammatePlayers ? owner->GetTeamNum() != pLocal->GetTeamNum() : true))
	//					{
	//						IMaterial *player_mat = (gESP.PlayerChams < 2 ? gMatHelper.shaded : gMatHelper.flat);
	//						ChamMode_t player_mode = ChamMode_t::DEFAULT;

	//						switch (gESP.PlayerChamsMode) {
	//							case 0: { player_mode = ChamMode_t::VISIBLE; break;	}
	//							case 1: { player_mode = ChamMode_t::INVISIBLE; break; }
	//							case 2: { player_mode = ChamMode_t::ALWAYS; break; }
	//						}

	//						was_chammed = true;
	//						chammed_mat = player_mat;
	//						chammed_col = gESP.ColWhite;
	//						chammed_mode = player_mode;
	//					}
	//				}
	//			}

	//			else if (ent->GetClassId() == CTFWearable)
	//			{
	//				CBaseEntity *owner = gInts.EntityList->GetClientEntityFromHandle(ent->GetOwner());

	//				if (owner && owner != pLocal)
	//				{
	//					if (gESP.Players && gESP.PlayerChams && (gESP.NoTeammatePlayers ? owner->GetTeamNum() != pLocal->GetTeamNum() : true))
	//					{
	//						IMaterial *player_mat = (gESP.PlayerChams < 2 ? gMatHelper.shaded : gMatHelper.flat);
	//						ChamMode_t player_mode = ChamMode_t::DEFAULT;

	//						switch (gESP.PlayerChamsMode) {
	//							case 0: { player_mode = ChamMode_t::VISIBLE; break;	}
	//							case 1: { player_mode = ChamMode_t::INVISIBLE; break; }
	//							case 2: { player_mode = ChamMode_t::ALWAYS; break; }
	//						}

	//						was_chammed = true;
	//						chammed_mat = player_mat;
	//						chammed_col = col;
	//						chammed_mode = player_mode;
	//					}
	//				}
	//			}
	//		}
	//	}	
	//}

	//if (was_chammed)
	//	cham(chammed_mat, chammed_col, chammed_mode);

	//else original(gInts.ModelRender, state, info, matrix);
}