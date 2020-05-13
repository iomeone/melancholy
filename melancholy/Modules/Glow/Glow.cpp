#include "Glow.h"

void CGlow::Run(CBaseEntity *pLocal, ClientFrameStage_t frame)
{
	static ConVar *glow_outline_effect_enable = gInts.ConVars->FindVar("glow_outline_effect_enable");
	glow_outline_effect_enable->SetValue(Active ? 1 : 0);

	//main glow handling
	if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (!Active || !gInts.Engine->IsConnected() || !gInts.Engine->IsInGame() || pLocal->GetTeamNum() < 2)
			return;

		for (int n = 1; n < gInts.EntityList->GetHighestEntityIndex(); n++)
		{
			CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

			if (!ent || ent == pLocal)
				continue;

			if (ent->IsPlayer())
			{
				bool cond = (ent->IsAlive() && !ent->IsDormant() && (NoTeammatePlayers ? ent->GetTeamNum() != pLocal->GetTeamNum() : true));

				ent->SetGlowEnabled(cond);

				if (cond)
				{
					int temp = 0;
					if (!ent->HasGlowEffect(temp)) {
						ent->UpdateGlowEffect();
					}
				}
			}

			else if (ent->IsBuilding())
			{
				bool cond = (ent->IsAlive() && !ent->IsDormant() && (NoTeammateBuildings ? ent->GetTeamNum() != pLocal->GetTeamNum() : true));

				ent->SetGlowEnabled(cond);

				if (cond)
				{
					int temp = 0;
					if (!ent->HasGlowEffect(temp)) {
						ent->UpdateGlowEffect();
					}
				}
			}
		}
	}

	//color handling
	if (frame == FRAME_RENDER_START)
	{
		for (int n = 0; n < gInts.GlowObject->m_GlowObjectDefinitions.Size(); n++)
		{
			GlowObjectDefinition_t &GlowObject = gInts.GlowObject->m_GlowObjectDefinitions[n];

			if (GlowObject.m_nNextFreeSlot != ENTRY_IN_USE)
				continue;

			if (!Active || pLocal->GetTeamNum() < 2) {
				GlowObject.m_flGlowAlpha = 0.0f; //kind of ghetto to handle it like this
				continue;
			}

			CBaseEntity *GlowEnt = gInts.EntityList->GetClientEntityFromHandle(GlowObject.m_hEntity);

			if (GlowEnt)
			{
				Vec3 GlowCol = Vec3();

				if (GlowEnt->IsPlayer())
				{
					if (NoTeammatePlayers && GlowEnt->GetTeamNum() == pLocal->GetTeamNum()) { //respawn glows fix
						GlowObject.m_flGlowAlpha = 0.0f;
						continue;
					}

					switch (PlayerGlow)
					{
						case 0: { GlowCol = Vec3(); break; }
						case 1: { GlowCol = Utils::GetTeamColor(GlowEnt->GetTeamNum()).V3(); break; }
						case 2: { GlowCol = Utils::GetHealthColor(GlowEnt->GetHealth(), GlowEnt->GetMaxHealth()).V3(); break; }
						case 3: { GlowCol = Utils::Rainbow().V3(); break; }
					}
				}

				else if (GlowEnt->IsBuilding())
				{
					if (NoTeammateBuildings && GlowEnt->GetTeamNum() == pLocal->GetTeamNum()) {
						GlowObject.m_flGlowAlpha = 0.0f;
						continue;
					}

					CObject *obj = reinterpret_cast<CObject *>(GlowEnt);

					if (obj)
					{
						switch (BuildingGlow)
						{
							case 0: { GlowCol = Vec3(); break; }
							case 1: { GlowCol = Utils::GetTeamColor(obj->GetTeamNum()).V3(); break; }
							case 2: { GlowCol = Utils::GetHealthColor(obj->GetHealth(), obj->GetMaxHealth()).V3(); break; }
							case 3: { GlowCol = Utils::Rainbow().V3(); break; }
						}
					}
				}

				GlowObject.m_vGlowColor = GlowCol;
				GlowObject.m_flGlowAlpha = GlowAlpha;
			}		
		}
	}
}

CGlow gGlow;