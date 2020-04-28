#include "Chams.h"

void CChams::Run()
{
	auto cham = [&](CBaseEntity *ent, IMaterial *mat, RGBA_t &col, ChamMode_t mode) -> void
	{
		if (!mat)
			return;	

		switch (mode)
		{
			case ChamMode_t::VISIBLE: {
				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				gMatHelper.ForceMaterial(mat, col, AlphaOverride);
				ent->DrawModel(0x1);
				break;
			}

			case ChamMode_t::INVISIBLE: {
				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				gMatHelper.ForceMaterial(mat, col, AlphaOverride);
				ent->DrawModel(0x1);

				gMatHelper.ResetMaterial();
				ent->DrawModel(0x1);
				break;
			}

			case ChamMode_t::ALWAYS: {
				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				gMatHelper.ForceMaterial(mat, col, AlphaOverride);
				ent->DrawModel(0x1);

				mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				gMatHelper.ForceMaterial(mat, col, AlphaOverride);
				ent->DrawModel(0x1);
				break;
			}
		}

		gMatHelper.ResetMaterial();
	};

	if (!Active || !gInts.Engine->IsConnected() || !gInts.Engine->IsInGame())
		return;

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (!pLocal || pLocal->GetTeamNum() < 2)
		return;

	for (int n = 1; n < gInts.EntityList->GetHighestEntityIndex(); n++)
	{
		CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

		if (!ent || ent == pLocal || !ent->IsAlive() || ent->IsDormant())
			continue;

		RGBA_t col = Utils::GetTeamColor(ent->GetTeamNum());

		if (ent->IsPlayer())
		{
			if (PlayerChams && (NoTeammatePlayers ? ent->GetTeamNum() != pLocal->GetTeamNum() : true))
			{
				IMaterial *mat = nullptr;
				switch (PlayerChams) {
					case 1: { mat = gMatHelper.shaded; break; }
					case 2: { mat = gMatHelper.flat; break; }
					case 3: { mat = gMatHelper.wireframe; break; }
				}

				ChamMode_t mode = ChamMode_t::DEFAULT;
				switch (PlayerChamsMode) {
					case 0: { mode = ChamMode_t::VISIBLE; break; }
					case 1: { mode = ChamMode_t::INVISIBLE; break; }
					case 2: { mode = ChamMode_t::ALWAYS; break; }
				}

				cham(ent, mat, col, mode);

				if (PlayerWeapons) {
					CBaseCombatWeapon *weapon = ent->GetActiveWeapon();

					static RGBA_t white = RGBA_t(255, 255, 255, 255);

					if (weapon)
						cham(weapon, mat, white, mode);
				}
			}
		}

		else if (ent->IsBuilding())
		{
			if (BuildingChams && (NoTeammateBuildings ? ent->GetTeamNum() != pLocal->GetTeamNum() : true))
			{
				IMaterial *mat = nullptr;
				switch (BuildingChams) {
					case 1: { mat = gMatHelper.shaded; break; }
					case 2: { mat = gMatHelper.flat; break; }
					case 3: { mat = gMatHelper.wireframe; break; }
				}

				ChamMode_t mode = ChamMode_t::DEFAULT;
				switch (BuildingChamsMode) {
					case 0: { mode = ChamMode_t::VISIBLE; break; }
					case 1: { mode = ChamMode_t::INVISIBLE; break; }
					case 2: { mode = ChamMode_t::ALWAYS; break; }
				}

				cham(ent, mat, col, mode);
			}
		}

		else if (ent->IsPickup())
		{
			if (PickupChams)
			{
				IMaterial *mat = nullptr;
				switch (PickupChams) {
					case 1: { mat = gMatHelper.shaded; break; }
					case 2: { mat = gMatHelper.flat; break; }
					case 3: { mat = gMatHelper.wireframe; break; }
				}

				ChamMode_t mode = ChamMode_t::DEFAULT;
				switch (PickupChamsMode) {
					case 0: { mode = ChamMode_t::VISIBLE; break; }
					case 1: { mode = ChamMode_t::INVISIBLE; break; }
					case 2: { mode = ChamMode_t::ALWAYS; break; }
				}

				RGBA_t col = Utils::GetPickupColor(ent);
				cham(ent, mat, col, mode);
			}
		}

		else if (ent->GetClassId() == CTFWearable)
		{
			CBaseEntity *owner = gInts.EntityList->GetClientEntityFromHandle(ent->GetOwner());

			if (!owner || owner == pLocal)
				continue;

			RGBA_t col = Utils::GetTeamColor(owner->GetTeamNum());

			if (PlayerChams && (NoTeammatePlayers ? owner->GetTeamNum() != pLocal->GetTeamNum() : true) && PlayerCosmetics)
			{
				IMaterial *mat = nullptr;
				switch (PlayerChams) {
					case 1: { mat = gMatHelper.shaded; break; }
					case 2: { mat = gMatHelper.flat; break; }
					case 3: { mat = gMatHelper.wireframe; break; }
				}

				ChamMode_t mode = ChamMode_t::DEFAULT;
				switch (PlayerChamsMode) {
					case 0: { mode = ChamMode_t::VISIBLE; break; }
					case 1: { mode = ChamMode_t::INVISIBLE; break; }
					case 2: { mode = ChamMode_t::ALWAYS; break; }
				}

				cham(ent, mat, col, mode);
			}
		}
	}
}

CChams gChams;