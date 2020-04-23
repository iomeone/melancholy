#include "ESP.h"

bool CESP::GetEntities(CBaseEntity *pLocal)
{
	if (!Entities.empty())
		Entities.clear();

	for (int n = 1; n < gInts.EntityList->GetHighestEntityIndex(); n++)
	{
		CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

		if (!ent || ent == pLocal || ent->IsDormant() || !ent->IsAlive())
			continue;

		if (ent->IsPlayer()) {
			if (!Players || NoTeammatePlayers && ent->GetTeamNum() == pLocal->GetTeamNum() || IgnoreCloaked && ent->IsCloaked())
				continue;

			Entities.push_back({ ESPEntType_t::PLAYER, ent, ent->GetAbsOrigin().DistTo(pLocal->GetAbsOrigin()) });
		}

		else if (ent->IsBuilding()) {
			if (!Buildings || NoTeammateBuildings && ent->GetTeamNum() == pLocal->GetTeamNum())
				continue;

			Entities.push_back({ ESPEntType_t::BUILDING, ent, ent->GetAbsOrigin().DistTo(pLocal->GetAbsOrigin()) });
		}

		else if (ent->IsPickup()) {
			if (!Pickups || !PickupName) //remove !PickupName if more stuff related to pickups is added.
				continue;

			Entities.push_back({ ESPEntType_t::PICKUP, ent, ent->GetAbsOrigin().DistTo(pLocal->GetAbsOrigin()) });
		}
	}

	if (Entities.empty())
		return false;

	std::sort(Entities.begin(), Entities.end(), [&](const ESPEnt_t &a, const ESPEnt_t &b) -> bool {
		return (a.dist > b.dist); //drawing order
	});

	return true;
}

bool CESP::GetEntityBoundsW2S(ESPEnt_t &ent, int &x_out, int &y_out, int &w_out, int &h_out)
{
	const matrix3x4 &transform = ent.ptr->GetRgflCoordinateFrame();

	Vec3 mins = Vec3();
	Vec3 maxs = Vec3();

	switch (ent.type)
	{
		case ESPEntType_t::PLAYER: {
			mins = gInts.GameMovement->GetPlayerMins(ent.ptr->IsDucking());
			maxs = gInts.GameMovement->GetPlayerMaxs(ent.ptr->IsDucking());
			break;
		}

		default: {
			mins = ent.ptr->GetCollideableMins();
			maxs = ent.ptr->GetCollideableMaxs();
			break;
		}
	}

	Vec3 points[] = {
		Vec3(mins.x, mins.y, mins.z),
		Vec3(mins.x, maxs.y, mins.z),
		Vec3(maxs.x, maxs.y, mins.z),
		Vec3(maxs.x, mins.y, mins.z),
		Vec3(maxs.x, maxs.y, maxs.z),
		Vec3(mins.x, maxs.y, maxs.z),
		Vec3(mins.x, mins.y, maxs.z),
		Vec3(maxs.x, mins.y, maxs.z)
	};

	Vec3 transformed_points[8];

	for (int i = 0; i < 8; i++)
		Math::VectorTransform(points[i], transform, transformed_points[i]);

	Vec3 ent_pos = ent.ptr->GetWorldSpaceCenter();
	Vec3 flb, brt, blb, frt, frb, brb, blt, flt;

	if (Math::W2S(transformed_points[3], flb) && Math::W2S(transformed_points[5], brt)
		&& Math::W2S(transformed_points[0], blb) && Math::W2S(transformed_points[4], frt)
		&& Math::W2S(transformed_points[2], frb) && Math::W2S(transformed_points[1], brb)
		&& Math::W2S(transformed_points[6], blt) && Math::W2S(transformed_points[7], flt)
		&& Math::W2S(transformed_points[6], blt) && Math::W2S(transformed_points[7], flt)) {
		Vec3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left		= flb.x;
		float top		= flb.y;
		float righ		= flb.x;
		float bottom	= flb.y;

		for (int n = 1; n < 8; n++) {
			if (left > arr[n].x)
				left = arr[n].x;

			if (top < arr[n].y)
				top = arr[n].y;

			if (righ < arr[n].x)
				righ = arr[n].x;

			if (bottom > arr[n].y)
				bottom = arr[n].y;
		}

		float x = left;
		float y = bottom;
		float w = (righ - left);
		float h = (top - bottom);

		if (ent.type == ESPEntType_t::PLAYER) {
			x += ((righ - left) / 8.0f);
			w -= (((righ - left) / 8.0f) * 2.0f);
		}

		x_out = static_cast<int>(x);
		y_out = static_cast<int>(y);
		w_out = static_cast<int>(w);
		h_out = static_cast<int>(h);

		if (x_out > gScreenSize.w || (x_out + w_out) < 0 || y_out > gScreenSize.h || (y_out + h_out) < 0)
			return false;

		return true;
	}

	return false;
}

RGBA_t CESP::GetEntityColor(ESPEnt_t &ent)
{
	RGBA_t out = RGBA_t();

	switch (ent.type)
	{
		case ESPEntType_t::PLAYER:
		{
			out = Utils::GetTeamColor(ent.ptr->GetTeamNum());

			if (!ent.ptr->IsVulnerable())
				out = ColInvuln;

			else if (ent.ptr->GetIndex() == gLocalInfo.CurrentTargetIndex && gAimbot.HighlightTarget)
				out = ColTarget;

			break;
		}

		case ESPEntType_t::BUILDING: {
			out = ((ent.ptr->GetIndex() == gLocalInfo.CurrentTargetIndex) ? ColTarget : Utils::GetTeamColor(ent.ptr->GetTeamNum()));
			break;
		}

		case ESPEntType_t::PICKUP: {
			out = Utils::GetPickupColor(ent.ptr);
			break;
		}
	}

	return out;
}

void CESP::Run()
{
	{
		static bool font_init = false;

		if (!font_init) {
			Draw = Draw_t("Arial", FontTall, 0, FONTFLAG_OUTLINE);
			DrawSmall = Draw_t("Smallest Pixel-7", FontTallSmall, 0, FONTFLAG_OUTLINE);
			font_init = true;
		}
	}

	if (!gInts.Engine->IsConnected() || !gInts.Engine->IsInGame() || gInts.Engine->Con_IsVisible() || gInts.EngineVGui->IsGameUIVisible())
		return;

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (!pLocal)
		return;

	if (pLocal->IsAlive()) {
		if (!gPredOut.pred_pos.IsZero()) {
			Vec3 pred_scrn = Vec3(), non_pred_scrn = Vec3();
			if (Math::W2S(gPredOut.pred_pos, pred_scrn) && Math::W2S(gPredOut.non_pred_pos, non_pred_scrn)) {
				Draw.Line(non_pred_scrn.x, non_pred_scrn.y, pred_scrn.x, pred_scrn.y, ColGreen);
			}
		}
	}

	if (!Active)
		return;

	if (!Spectators.empty())
		Spectators.clear();

	if (pLocal->IsAlive())
	{
		if (SpectatorList)
		{
			for (int n = 0; n < (gInts.Engine->GetMaxClients() + 1); n++)
			{
				CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

				if (!ent || ent == pLocal || !ent->IsPlayer() || ent->IsAlive())
					continue;

				PlayerInfo_t info;

				if (!gInts.Engine->GetPlayerInfo(ent->GetIndex(), &info))
					continue;

				CBaseEntity *obs_target = gInts.EntityList->GetClientEntityFromHandle(ent->GetObserverTarget());

				if (!obs_target || obs_target != pLocal || !obs_target->IsAlive())
					continue;

				auto GetMode = [&](CBaseEntity *ent) -> std::string {
					switch (ent->GetObserverMode()) {
						case OBS_MODE_FIRSTPERSON: { return "firstperson"; }
						case OBS_MODE_THIRDPERSON: { return "thirdperson"; }
						default: return "BOO!";
					}
				};

				std::string mode = GetMode(ent);

				if (mode == "BOO!")
					continue;

				Spectators.push_back({ info.name, mode });
			}
		}
	}
	
	if (GetEntities(pLocal))
	{
		for (auto &v : Entities)
		{
			int x = 0, y = 0, w = 0, h = 0;

			if (!GetEntityBoundsW2S(v, x, y, w, h))
				continue;
			
			static int healthbar_size	= 3;
			static int healthbar_offset = 2; //if vertically - otherwise +
			int text_x					= ((x + w) + 2);
			int text_y					= y;
			int text_offset				= 0; //updated after each text draw

			RGBA_t col = GetEntityColor(v);

			switch (v.type)
			{
				case ESPEntType_t::PLAYER:
				{
					if (PlayerTextPos == 0) {
						text_x = ((x + w) + 2);
						text_y = y;
					}

					else if (PlayerTextPos == 1) {
						text_x = x;

						if (PlayerHealthBar == 2)
							text_y = (y + h + (healthbar_size + 1));

						else text_y = (y + h);
					}

					else if (PlayerTextPos == 2) {
						Vec3 wsc_3d = v.ptr->GetHitboxPos(HITBOX_BODY);
						Vec3 wsc_2d = Vec3();

						if (Math::W2S(wsc_3d, wsc_2d))
						{
							if (wsc_2d.x > gScreenSize.w || wsc_2d.x < 0 || wsc_2d.y > gScreenSize.h || wsc_2d.y < 0)
								continue;

							text_x = static_cast<int>(wsc_2d.x);
							text_y = static_cast<int>(wsc_2d.y);
						}
					}


					if (PlayerBones)
					{
						studiohdr_t *pStudioHdr = reinterpret_cast<studiohdr_t *>(gInts.ModelInfo->GetStudioModel(v.ptr->GetModel()));

						if (pStudioHdr)
						{
							Vec3 parent0 = Vec3();
							Vec3 parent1 = Vec3();
							Vec3 child0 = Vec3();
							Vec3 child1 = Vec3();

							for (int n = 0; n < pStudioHdr->numbones; n++) {
								mstudiobone_t *pBone = pStudioHdr->GetBone(n);

								if (pBone && (pBone->flags & 0x100) && (pBone->parent != -1)) {
									child0 = v.ptr->GetBonePos(n);
									parent0 = v.ptr->GetBonePos(pBone->parent);

									if (Math::W2S(parent0, parent1) && Math::W2S(child0, child1))
										Draw.Line(parent1.x, parent1.y, child1.x, child1.y, (PlayerBones < 2 ? col : ColWhite));
								}
							}
						}
					}

					if (PlayerBox)
					{
						Draw.OutlinedRect(x, y, w, h, col);
						Draw.OutlinedRect(x - 1, y - 1, w + 2, h + 2, ColOutline);
					}

					if (PlayerHealthBar)
					{
						float hp = static_cast<float>(v.ptr->GetHealth());
						float max_hp = static_cast<float>(v.ptr->GetMaxHealth());

						if (hp > max_hp)
							hp = max_hp;

						RGBA_t col = Utils::GetHealthColor(v.ptr->GetHealth(), v.ptr->GetMaxHealth());

						if (PlayerHealthBar == 1) {
							if (hp < max_hp)
								h += 1; //don't ask me, I calculated the pixels and decided this. POST NOTE: sometimes it still draws 1px too little smh

							Draw.Rect((x - (healthbar_offset + 3)), (y - 1), (healthbar_size + 2), (h + (hp < max_hp ? 1 : 2)), ColOutline);
							Draw.Rect((x - (healthbar_offset + 2)), (y + (h - (h / max_hp * hp))), healthbar_size, (h / max_hp * hp), col);
						}

						else if (PlayerHealthBar == 2) {
							float p = ((1.0f - hp / max_hp) / 2.0f);
							Draw.Rect(x - 1, ((y + h) + healthbar_offset - 2), (w + 2), (healthbar_size + 2), ColOutline);
							Draw.Rect((x + w * p), ((y + h) + (healthbar_offset - 1)), (w - w * p * 2), healthbar_size, col);
						}
					}

					//draw the text over bars, boxes...

					if (PlayerName)
					{
						PlayerInfo_t info;

						if (gInts.Engine->GetPlayerInfo(v.ptr->GetIndex(), &info)) {
							Draw.String(text_x, (text_y + text_offset), col, info.name);
							text_offset += FontTall;
						}
					}

					if (PlayerClass)
					{
						Draw.String(text_x, (text_y + text_offset), col, v.ptr->szGetClass());
						text_offset += FontTall;
					}

					if (PlayerHealth)
					{
						RGBA_t col = Utils::GetHealthColor(v.ptr->GetHealth(), v.ptr->GetMaxHealth());
						Draw.String(text_x, (text_y + text_offset), col, std::to_string(v.ptr->GetHealth()).c_str());
						text_offset += FontTall;
					}

					if (PlayerCond)
					{
						std::string cond_str = "";

						if (v.ptr->IsUbered())
							cond_str += "UBERED | ";

						if (v.ptr->IsBonked())
							cond_str += "BONKED | ";

						if (v.ptr->IsCritBoosted())
							cond_str += "KRITZED | ";

						if (v.ptr->IsCloaked())
							cond_str += "CLOAKED | ";

						if (v.ptr->IsScoped())
							cond_str += "SCOPED | ";

						if (v.ptr->IsTaunting())
							cond_str += "TAUNTING | ";

						if (cond_str.size() > 0)
							cond_str.erase((cond_str.end() - 3), (cond_str.end() - 1));

						int str_w = 0, str_h = 0;
						gInts.Surface->GetTextSize(DrawSmall.dwFont, Utils::ToWC(cond_str.c_str()), str_w, str_h);
						DrawSmall.String((x + (w / 2) - (str_w / 2)), (y - (FontTallSmall - 2)), ColWhite, cond_str.c_str());
					}

					break;
				}

				case ESPEntType_t::BUILDING:
				{
					if (BuildingTextPos == 0) {
						text_x = ((x + w) + 2);
						text_y = y;
					}

					else if (BuildingTextPos == 1) {
						text_x = x;

						if (BuildingHealthBar == 2)
							text_y = (y + h + (healthbar_size + 1));

						else text_y = (y + h);
					}

					else if (BuildingTextPos == 2) {
						Vec3 wsc_3d = v.ptr->GetWorldSpaceCenter();
						Vec3 wsc_2d = Vec3();

						if (Math::W2S(wsc_3d, wsc_2d))
						{
							if (wsc_2d.x > gScreenSize.w || wsc_2d.x < 0 || wsc_2d.y > gScreenSize.h || wsc_2d.y < 0)
								continue;

							text_x = static_cast<int>(wsc_2d.x);
							text_y = static_cast<int>(wsc_2d.y);
						}
					}


					if (BuildingBox)
					{
						Draw.OutlinedRect(x, y, w, h, col);
						Draw.OutlinedRect(x - 1, y - 1, w + 2, h + 2, ColOutline);
					}

					if (BuildingHealthBar)
					{
						CObject *obj = reinterpret_cast<CObject *>(v.ptr);

						if (obj)
						{
							float hp = static_cast<float>(obj->GetHealth());
							float max_hp = static_cast<float>(obj->GetMaxHealth());

							if (hp > max_hp)
								hp = max_hp;

							RGBA_t col = Utils::GetHealthColor(obj->GetHealth(), obj->GetMaxHealth());

							if (BuildingHealthBar == 1) {
								if (hp < max_hp)
									h += 1;

								Draw.Rect((x - (healthbar_offset + 3)), (y - 1), (healthbar_size + 2), (h + (hp < max_hp ? 1 : 2)), ColOutline);
								Draw.Rect((x - (healthbar_offset + 2)), (y + (h - (h / max_hp * hp))), healthbar_size, (h / max_hp * hp), col);
							}

							else if (BuildingHealthBar == 2) {
								float p = ((1.0f - hp / max_hp) / 2.0f);
								Draw.Rect(x - 1, ((y + h) + healthbar_offset - 2), (w + 2), (healthbar_size + 2), ColOutline);
								Draw.Rect((x + w * p), ((y + h) + (healthbar_offset - 1)), (w - w * p * 2), healthbar_size, col);
							}
						}
					}

					if (BuildingName)
					{
						std::string name = "";

						switch (v.ptr->GetClassId()) {
							case CObjectSentrygun: { name = "sentrygun"; break; }
							case CObjectDispenser: { name = "dispenser"; break; }
							case CObjectTeleporter: { name = "teleporter"; break; }
						}

						name += (" " + std::to_string(reinterpret_cast<CObject *>(v.ptr)->GetLevel()));

						Draw.String(text_x, (text_y + text_offset), col, name.c_str());
						text_offset += FontTall;
					}

					if (BuildingHealth)
					{
						CObject *obj = reinterpret_cast<CObject *>(v.ptr);

						if (obj) {
							RGBA_t col = Utils::GetHealthColor(obj->GetHealth(), obj->GetMaxHealth());
							Draw.String(text_x, (text_y + text_offset), col, std::to_string(obj->GetHealth()).c_str());
							text_offset += FontTall;
						}
					}

					if (BuildingCond)
					{
						CObject *obj = reinterpret_cast<CObject *>(v.ptr);

						if (obj && obj->IsSapped()) {
							static std::string cond_str = "SAPPED";
							int str_w = 0, str_h = 0;
							gInts.Surface->GetTextSize(DrawSmall.dwFont, Utils::ToWC(cond_str.c_str()), str_w, str_h);
							DrawSmall.String((x + (w / 2) - (str_w / 2)), (y - (FontTallSmall - 2)), ColWhite, cond_str.c_str());
						}
					}

					break;
				}

				case ESPEntType_t::PICKUP:
				{
					if (PickupName)
					{
						const char *model_name = v.ptr->GetModelName();

						std::string name_str = "";

						if (model_name[13] == 'm' && model_name[20] == 's'
							|| model_name[33] == 'm' && model_name[40] == 's')
							name_str = "health";		//"small medkit"

						else if (model_name[13] == 'm' && model_name[20] == 'm'
							|| model_name[33] == 'm' && model_name[40] == 'm')
							name_str = "health";		//"medium medkit"

						else if (model_name[13] == 'm' && model_name[20] == 'l'
							|| model_name[33] == 'm' && model_name[40] == 'l')
							name_str = "health";		//"large medkit"

						else if (model_name[13] == 'p' && model_name[16] == 't'
							|| model_name[24] == 's' && model_name[28] == 'w')
							name_str = "sandwich";		//"sandwich"

						else if (model_name[13] == 'a' && model_name[22] == 's')
							name_str = "ammo";			//"small ammo"

						else if (model_name[13] == 'a' && model_name[22] == 'm')
							name_str = "ammo";			//"medium ammo"

						else if (model_name[13] == 'a' && model_name[22] == 'l')
							name_str = "ammo";			//"large ammo"

						if (!name_str.empty()) {
							int str_w = 0, str_h = 0;
							gInts.Surface->GetTextSize(DrawSmall.dwFont, Utils::ToWC(name_str.c_str()), str_w, str_h);
							DrawSmall.String((x + (w / 2) - (str_w / 2)), (y + (h / 2) - (str_h / 2)), col, name_str.c_str());
						}
					}

					break;
				}
			}
		}
	}
}

void CESP::ReloadFonts() {
	Draw = Draw_t("Arial", FontTall, 0, FONTFLAG_OUTLINE);
	DrawSmall = Draw_t("Smallest Pixel-7", FontTallSmall, 0, FONTFLAG_OUTLINE);
}

CESP gESP;