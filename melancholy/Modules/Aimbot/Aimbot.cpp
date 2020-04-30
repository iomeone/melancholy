#include "Aimbot.h"

Vec3 SmoothStartAngle	= Vec3();
float SmoothStartTime	= 0.0f;
bool AimFinished		= false;	//used for projectile autoshoot (kinda sucks)
int OldAimPoint			= -1;		//used for reseting smoothing

CAimbot::Target_t CAimbot::GetTarget(CBaseEntity *pLocal, CBaseCombatWeapon *wep, CUserCmd *cmd)
{
	Targets.reserve(12); //not a problem if there's more

	if (!Targets.empty())
		Targets.clear();

	Vec3 LocalPos		= pLocal->GetShootPos();
	Vec3 LocalAngles	= cmd->viewangles;
	bool is_melee		= (wep->GetSlot() == 2 && AimMelee);
	int hitbox			= GetAimHitbox(pLocal, wep);

	int loop_range = ((AimSentry || AimDispenser || AimTeleporter) ? gInts.EntityList->GetHighestEntityIndex() : (gInts.Engine->GetMaxClients() + 1));

	for (int n = 1; n < loop_range; n++)
	{
		CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

		if (!ent 
			|| ent == pLocal 
			|| (!ent->IsPlayer() && !ent->IsBuilding())
			|| ent->GetTeamNum() == pLocal->GetTeamNum()
			|| ent->IsDormant()
			|| !ent->IsAlive())
			continue;

		bool is_building = false;

		if (ent->IsPlayer())
		{
			if (!ent->IsVulnerable())
				continue;

			if (IgnoreCloaked && ent->IsCloaked() || IgnoreTaunting && ent->IsTaunting())
				continue;

			if (RemoveDisguise)
				ent->RemoveCond(TFCond_Disguised);
		}

		else if (ent->IsBuilding())
		{
			if (!AimSentry && !AimDispenser && !AimTeleporter)
				continue;

			if (!AimSentry && ent->GetClassId() == CObjectSentrygun)
				continue;

			if (!AimDispenser && ent->GetClassId() == CObjectDispenser)
				continue;

			if (!AimTeleporter && ent->GetClassId() == CObjectTeleporter)
				continue;

			is_building = true;
		}

		Vec3 ent_pos	= (is_building ? ent->GetWorldSpaceCenter() : ent->GetHitboxPos(hitbox));
		Vec3 ang_to_ent = Math::CalcAngle(LocalPos, ent_pos);
		float fov		= Math::CalcFov(LocalAngles, ang_to_ent);
		float dist		= ent_pos.DistTo(LocalPos);

		Targets.emplace_back(Target_t{ ent, fov, dist, ang_to_ent, ent_pos, LocalPos });
	}

	if (Targets.empty())
		return {}; //if it's empty abort

	std::sort(Targets.begin(), Targets.end(), [&](const Target_t &a, const Target_t &b) -> bool {
		return ((is_melee && AimAtClosest) ? (a.dist < b.dist) : (a.fov < b.fov));
	});
	
	for (auto &v : Targets)
	{	
		if (is_melee)
		{
			if (InRangeOnly && !Utils::CanMeleeHit(wep, v.ang_to_ent, v.ptr->GetIndex()))
				continue;
			
			if (AimAtClosest)
				return v; //these are sorted already!
		}

		if (v.fov < AimFov)
			return v;
	}

	return {};
}

bool CAimbot::CorrectAimPos(CBaseEntity *pLocal, CBaseCombatWeapon *wep, CUserCmd *cmd, Target_t &target)
{
	//this entire thing needs a lot of cleaning

	Vec3 LocalAngles = cmd->viewangles;

	if (target.ptr->IsPlayer())
	{
		int hitbox = GetAimHitbox(pLocal, wep);

		//projectile correction
		CProjectileWeapon ProjectileWep(wep);
		ProjectileInfo_t ProjectileInfo = ProjectileWep.GetWeaponInfo();

		if (ProjectileInfo.speed > 0.0f)
		{
			if (!ProjectileAim)
				return false;

			switch (pLocal->GetClassNum())
			{
				case TF2_Soldier: {
					target.ent_pos.z -= 30.0f;
					break;
				}

				case TF2_Demoman:
				{
					Vec3 vecForward = Vec3(), vecRight = Vec3(), vecUp = Vec3();
					Math::AngleVectors(cmd->viewangles, &vecForward, &vecRight, &vecUp);
					target.local_pos += ((vecForward * 16.0f) + (vecRight * 8.0f) + (vecUp * -6.0f));
					//target.ent_pos.z -= 35.0f;
					break;
				}
			}

			CPredictor Predictor(target.ent_pos, target.ptr->GetVelocity(), Vec3(0.0f, 0.0f, 800.0f), target.ptr);
			Solution_t Solution = {};

			//vis checking is done inside this func
			if (Solve(target.local_pos, ProjectileWep, Predictor, Solution, target.ptr->IsOnGround()))
			{
				target.ang_to_ent = { -RAD2DEG(Solution.pitch), RAD2DEG(Solution.yaw), 0.0f };

				if (pLocal->GetClassNum() == TF2_Demoman) {
					Vec3 vecForward, vecRight, vecUp;
					Math::AngleVectors(target.ang_to_ent, &vecForward, &vecRight, &vecUp);
					float mod = (!target.ptr->IsOnGround() && target.ptr->GetVelocity().z < 0.0f ? 200.0f : 100.0f);
					Vec3 vecVelocity = ((vecForward * ProjectileInfo.speed) - (vecUp * mod));
					Math::VectorAngles(vecVelocity, target.ang_to_ent);
				}

				target.fov = Math::CalcFov(LocalAngles, target.ang_to_ent);
				return true;
			}

			return false;
		}

		//hitscan correction
		else
		{
			int vis_hitbox = -1;

			//if the pos is not visible (or if we're aiming at the head but the hitbox is not head) try some corrections
			if (!Utils::Vis_Pos_IdOut(pLocal, target.ptr, target.local_pos, target.ent_pos, vis_hitbox) || (hitbox == HITBOX_HEAD && vis_hitbox != hitbox))
			{
				//multipoint
				if (hitbox == HITBOX_HEAD)
				{
					if (!Multipoint)
						return false;

					DWORD *model = target.ptr->GetModel();
					if (!model)
						return false;

					studiohdr_t *hdr = reinterpret_cast<studiohdr_t *>(gInts.ModelInfo->GetStudioModel(model));
					if (!hdr)
						return false;

					matrix3x4 bone_matrix[128];
					if (!target.ptr->SetupBones(bone_matrix, 128, 0x100, gInts.Globals->curtime))
						return false;

					mstudiohitboxset_t *set = hdr->GetHitboxSet(target.ptr->GetHitboxSet());
					if (!set)
						return false;

					mstudiobbox_t *box = set->pHitbox(HITBOX_HEAD);
					if (!box)
						return false;

					Vec3 mins = (box->bbmin * 0.75f); //scale them down a bit for accuraccy reasons
					Vec3 maxs = (box->bbmax * 0.75f);

					Vec3 points[5] = {
						Vec3(((mins.x + maxs.x) * 0.5f), ((mins.y + maxs.y) * 0.5f), maxs.z), //top center for aim height meme
						Vec3(maxs.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)), //sides center:
						Vec3(mins.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)),
						Vec3(((mins.x + maxs.x) * 0.5f), maxs.y, ((mins.z + maxs.z) * 0.5f)),
						Vec3(((mins.x + maxs.x) * 0.5f), mins.y, ((mins.z + maxs.z) * 0.5f))
					};

					Vec3 out[5] = { Vec3() };

					for (int n = 0; n < 5; n++)
					{
						Math::VectorTransform(points[n], bone_matrix[box->bone], out[n]);

						if (Utils::Vis_Pos_Id(pLocal, target.ptr, target.local_pos, out[n], HITBOX_HEAD))
						{
							target.ang_to_ent = Math::CalcAngle(target.local_pos, out[n]);

							if (n != OldAimPoint) {
								OldAimPoint = n;
								SmoothStartTime = gInts.Globals->curtime;
								SmoothStartAngle = cmd->viewangles;
							}

							return true;
						}
					}

					//all points were checked and nothing was found, return
					return false;
				}

				//hitscan
				else if (hitbox == HITBOX_PELVIS)
				{
					if (!Hitscan)
						return false;

					for (int n = 1; n < target.ptr->GetNumOfHitboxes(); n++)
					{
						Vec3 vis_body = target.ptr->GetHitboxPos(n);

						if (Utils::Vis_Pos(pLocal, target.ptr, target.local_pos, vis_body))
						{
							target.ang_to_ent = Math::CalcAngle(target.local_pos, vis_body);

							if (n != OldAimPoint) {
								OldAimPoint = n;
								SmoothStartTime = gInts.Globals->curtime;
								SmoothStartAngle = cmd->viewangles;
							}

							return true;
						}
					}

					//all hitboxes were checked and nothing was found, return
					return false;
				}
			}
		}
	}

	else //this is kinda a mess, I just tried it and it worked so /shrug
	{
		Ray_t ray;
		ray.Init(target.local_pos, target.ent_pos);
		CTraceFilter filter;
		filter.pSkip = target.ptr;
		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, MASK_SHOT_HULL, &filter, &trace);

		int found = 1;

		if (trace.fraction < 0.99f)
		{
			found = 0;

			matrix3x4 &transform = target.ptr->GetRgflCoordinateFrame();

			Vec3 mins = (target.ptr->GetCollideableMins() * 0.85f);
			Vec3 maxs = (target.ptr->GetCollideableMaxs() * 0.85f);

			Vec3 points[5] = {
				Vec3(((mins.x + maxs.x) * 0.5f), ((mins.y + maxs.y) * 0.5f), maxs.z),
				Vec3(maxs.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)),
				Vec3(mins.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)),
				Vec3(((mins.x + maxs.x) * 0.5f), maxs.y, ((mins.z + maxs.z) * 0.5f)),
				Vec3(((mins.x + maxs.x) * 0.5f), mins.y, ((mins.z + maxs.z) * 0.5f))
			};

			Vec3 out[5] = { Vec3() };

			for (int n = 0; n < 5; n++)
			{
				Math::VectorTransform(points[n], transform, out[n]);

				Ray_t ray;
				ray.Init(target.local_pos, out[n]);
				CTraceFilter filter;
				filter.pSkip = target.ptr;
				CGameTrace trace;
				gInts.EngineTrace->TraceRay(ray, MASK_SHOT_HULL, &filter, &trace);

				if (trace.fraction > 0.98f)
				{
					target.ent_pos = out[n];
					found = 1;

					if (n != OldAimPoint) {
						OldAimPoint = n;
						SmoothStartTime = gInts.Globals->curtime;
						SmoothStartAngle = cmd->viewangles;
					}
				}
			}
		}

		if (found)
		{
			CProjectileWeapon ProjectileWep(wep);

			if (ProjectileWep.GetWeaponInfo().gravity > 0.0f)
			{
				if (!ProjectileAim)
					return false;

				switch (pLocal->GetClassNum()) {
					case TF2_Demoman: {
						target.ent_pos.z -= 5.0f;
						break;
					}
				}

				CPredictor Predictor(target.ent_pos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), target.ptr);
				Solution_t Solution = {};

				if (Solve(target.local_pos, ProjectileWep, Predictor, Solution, true)) {
					target.ang_to_ent = { -RAD2DEG(Solution.pitch), RAD2DEG(Solution.yaw), 0.0f };
					return true;
				}
			}

			else target.ang_to_ent = Math::CalcAngle(target.local_pos, target.ent_pos);
		}

		else return false;
	}

	return true;
}

int CAimbot::GetAimHitbox(CBaseEntity *pLocal, CBaseCombatWeapon *wep)
{
	if (AimHitbox == 0)
		return HITBOX_HEAD;

	else if (AimHitbox == 1)
		return HITBOX_PELVIS;

	else if (AimHitbox == 2)
	{
		int wep_slot = wep->GetSlot();

		if (wep_slot == 2)
			return HITBOX_BODY;

		int wep_idx = wep->GetItemDefinitionIndex();

		switch (pLocal->GetClassNum()) {
			case TF2_Sniper:
				return (wep_slot == 0 ? HITBOX_HEAD : HITBOX_PELVIS);
			case TF2_Spy:
				return ((wep_idx == Spy_m_TheAmbassador || wep_idx == Spy_m_FestiveAmbassador) ? HITBOX_HEAD : HITBOX_PELVIS);
			default:
				return HITBOX_PELVIS;
		}
	}

	return 0;
}

bool CAimbot::IsAimKeyDown() {
	return (AimKey < 1 ? (GetAsyncKeyState(VK_LSHIFT) & 0x8000) : (GetAsyncKeyState(VK_LBUTTON) & 0x8000));
}

void CAimbot::SetAngles(CBaseEntity *pLocal, Target_t &target, CUserCmd *cmd)
{
	Math::ClampAngles(target.ang_to_ent);

	if (AimTime > 0.0f)
	{
		cmd->viewangles = SmoothStartAngle;
		float time = std::clamp(((gInts.Globals->curtime - SmoothStartTime) / AimTime), 0.0f, 1.0f);
		Vec3 delta = (target.ang_to_ent - SmoothStartAngle);
		Math::ClampAngles(delta);
		cmd->viewangles += (delta * (AimMethod < 1 ? time : Math::ExponentialEaseOut(time)));
		gInts.Engine->SetViewAngles(cmd->viewangles);
		AimFinished = (time > 0.99f);
	}

	else
	{
		if (Silent) {
			Utils::FixSilentMovement(cmd, target.ang_to_ent);
			cmd->viewangles = target.ang_to_ent;
			return;
		}

		cmd->viewangles = target.ang_to_ent;
		gInts.Engine->SetViewAngles(target.ang_to_ent);
	}
}

bool CAimbot::ShouldAutoshoot(CBaseEntity *pLocal, CBaseCombatWeapon *wep, Target_t &target, CUserCmd *cmd)
{
	if (AimTime > 0.0f)
	{
		if (!AimFinished)
		{
			CProjectileWeapon ProjectileWep(wep);

			if (ProjectileWep.GetWeaponInfo().speed > 0.0f)
				return false;

			else //this is basically a triggerbot
			{
				Vec3 vForward = Vec3();
				Math::AngleVectors(cmd->viewangles, &vForward);
				Vec3 vTraceStart = target.local_pos;
				Vec3 vTraceEnd = (vTraceStart + (vForward * 9999.0f));

				Ray_t ray;
				ray.Init(vTraceStart, vTraceEnd);
				CTraceFilter filter;
				filter.pSkip = pLocal;
				CGameTrace trace;
				gInts.EngineTrace->TraceRay(ray, ((target.ptr->IsPlayer() ? MASK_SHOT : MASK_SHOT_HULL) | CONTENTS_GRATE), &filter, &trace);

				static float timer = gInts.Globals->curtime;

				//if we're already on a target, shoot even if aim (smooth) hasn't finished
				if (trace.m_pEnt && trace.m_pEnt->GetIndex() == target.ptr->GetIndex()) {
					if (GetAimHitbox(pLocal, wep) == HITBOX_HEAD && trace.hitbox != HITBOX_HEAD)
						return false;

					if ((gInts.Globals->curtime - timer) < 0.05f) //wait a bit so we don't shoot the very edge of the hitbox
						return false;
				}

				else
				{
					timer = gInts.Globals->curtime;
					return false;
				}
			}
		}
	}

	//do all the other checks after the aim is done

	int wep_slot	= wep->GetSlot();
	int wep_idx		= wep->GetItemDefinitionIndex();
	int class_num	= pLocal->GetClassNum();

	if (class_num == TF2_Spy && wep_slot == 2 && target.ptr->IsPlayer())
	{
		if (AimMelee && AutoBackstab)
		{
			if (Utils::CanMeleeHit(wep, target.ang_to_ent, target.ptr->GetIndex())) {
				if (Utils::CanBackstab(cmd->viewangles, target.ptr->GetEyeAngles(), (target.ptr->GetWorldSpaceCenter() - pLocal->GetWorldSpaceCenter())))
					return true;
			}
			
			return false;
		}
	}

	if (!Autoshoot)
		return false;

	if (wep_slot < 2)
	{
		if (class_num == TF2_Sniper) {
			if (wep_slot == 0 && pLocal->IsScoped() && WaitForHS && !gLocalInfo.CanHeadShot)
				return false;
		}

		else if (class_num == TF2_Spy) {
			if ((wep_idx == Spy_m_TheAmbassador || wep_idx == Spy_m_FestiveAmbassador) && WaitForHS && !gLocalInfo.CanHeadShot)
				return false;
		}
	}

	else if (wep_slot == 2)
	{
		if (AimMelee && !InRangeOnly) {
			if (!Utils::CanMeleeHit(wep, target.ang_to_ent, target.ptr->GetIndex()))
				return false;
		}
	}

	return true;
}

bool CAimbot::TargetChanged()
{
	static int old_target = gLocalInfo.CurrentTargetIndex;

	if (gLocalInfo.CurrentTargetIndex != old_target) {
		old_target = gLocalInfo.CurrentTargetIndex;
		OldAimPoint = -1;
		return true;
	}

	return false;
}

void CAimbot::Run(CBaseEntity *pLocal, CBaseCombatWeapon *pLocalWeapon, CUserCmd *cmd)
{
	if (!Active
		|| !pLocal->IsAlive()
		|| pLocal->IsTaunting()
		|| !gInts.Engine->IsConnected()
		|| !gInts.Engine->IsInGame()
		|| gInts.Engine->Con_IsVisible())
		return;

	if (!AimMelee && pLocalWeapon->GetSlot() == 2)
		return;

	Target_t target = GetTarget(pLocal, pLocalWeapon, cmd);

	if (target.ptr)
	{
		if (!CorrectAimPos(pLocal, pLocalWeapon, cmd, target)) {
			SmoothStartTime = gInts.Globals->curtime;
			SmoothStartAngle = cmd->viewangles;
			return;

			//CONS: since at this stage we only have one target,
			//		returning here means not aiming at someone else
			//PROS: very cheap to do as we do all the correction checks for 1 entity only
		}

		int wep_idx = pLocalWeapon->GetItemDefinitionIndex();
		static int old_wep_idx = wep_idx;

		if (wep_idx != old_wep_idx) {
			old_wep_idx = wep_idx;
			SmoothStartTime = gInts.Globals->curtime;
			SmoothStartAngle = cmd->viewangles;
		}

		if (ScopedOnly && (pLocal->GetClassNum() == TF2_Sniper && pLocalWeapon->GetSlot() == 0 && !pLocal->IsScoped()))
		{
			if (wep_idx != Sniper_m_TheHuntsman && wep_idx != Sniper_m_FestiveHuntsman && wep_idx != Sniper_m_TheFortifiedCompound) {
				SmoothStartTime = gInts.Globals->curtime;
				SmoothStartAngle = cmd->viewangles;
				return;
			}
		}

		if (IsAimKeyDown())
		{
			gLocalInfo.CurrentTargetIndex = target.ptr->GetIndex();

			if (TargetChanged()) {
				SmoothStartTime = gInts.Globals->curtime;
				SmoothStartAngle = cmd->viewangles;
			}

			SetAngles(pLocal, target, cmd);

			if (ShouldAutoshoot(pLocal, pLocalWeapon, target, cmd))
				cmd->buttons |= IN_ATTACK;
		}

		else {
			SmoothStartTime = gInts.Globals->curtime;
			SmoothStartAngle = cmd->viewangles;
		}
	}

	else {
		SmoothStartTime = gInts.Globals->curtime;
		SmoothStartAngle = cmd->viewangles;
	}
}

CAimbot gAimbot;