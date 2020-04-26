#include "Glow.h"

void CGlow::Run(CBaseEntity *pLocal, ClientFrameStage_t frame)
{
	//main glow handling
	if (frame == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (!Active || !gInts.Engine->IsConnected() || !gInts.Engine->IsInGame())
			return;

		for (int n = 1; n < gInts.EntityList->GetHighestEntityIndex(); n++) {
			CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

			if (!ent || ent == pLocal || (!ent->IsPlayer() && !ent->IsBuilding())) //fuck glowing other entities (crashing 24/7)
				continue;

			ent->SetGlowEnabled(ent->IsAlive() && !ent->IsDormant());

			if (ent->IsGlowEnabled())
				ent->UpdateGlowEffect();
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

			if (!Active) {
				GlowObject.m_flGlowAlpha = 0.0f; //kind of ghetto to handle it like this
				continue;
			}

			CBaseEntity *GlowEnt = gInts.EntityList->GetClientEntityFromHandle(GlowObject.m_hEntity);

			if (!GlowEnt)
				continue;

			Vec3 GlowCol = Vec3();

			if (GlowEnt->IsPlayer() && PlayerGlow && (NoTeammatePlayers ? GlowEnt->GetTeamNum() != pLocal->GetTeamNum() : true))
			{
				switch (PlayerGlow) {
					case 0: { GlowCol = Vec3(); break; }
					case 1: { GlowCol = Utils::GetTeamColor(GlowEnt->GetTeamNum()).V3(); break; }
					case 2: { GlowCol = Utils::GetHealthColor(GlowEnt->GetHealth(), GlowEnt->GetMaxHealth()).V3(); break; }
				}
			}
			
			else if (GlowEnt->IsBuilding() && BuildingGlow && (NoTeammateBuildings ? GlowEnt->GetTeamNum() != pLocal->GetTeamNum() : true))
			{
				CObject *obj = reinterpret_cast<CObject *>(GlowEnt);

				if (obj)
				{
					switch (BuildingGlow) {
						case 0: { GlowCol = Vec3(); break; }
						case 1: { GlowCol = Utils::GetTeamColor(obj->GetTeamNum()).V3(); break; }
						case 2: { GlowCol = Utils::GetHealthColor(obj->GetHealth(), obj->GetMaxHealth()).V3(); break; }
					}
				}
			}

			GlowObject.m_vGlowColor = GlowCol;
			GlowObject.m_flGlowAlpha = GlowAlpha;
		}
	}
}

CGlow gGlow;