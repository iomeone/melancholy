#include "Aimbot.h"

//TODO: find some magic way to predict moving entities for improved accuraccy,
//it misses quite a lot at players who are moving very fast through the air.
//That or there's some missing local player prediction stuff (I'm pretty sure something besides "engine pred" can be done) to improve the accuraccy even more

Vec3 SmoothStartAngle = Vec3();
float SmoothStartTime = 0.0f;

CAimbot::Target_t CAimbot::GetTarget(CBaseEntity *pLocal, CBaseCombatWeapon *wep, CUserCmd *cmd)
{
	if (!Targets.empty())
		Targets.clear();

	Vec3 LocalPos		= pLocal->GetShootPos();
	Vec3 LocalAngles	= cmd->viewangles;
	bool is_melee		= (wep->GetSlot() == 2 && AimMelee);
	int hitbox			= GetAimHitbox(pLocal, wep);

	for (int n = 1; n < (gInts.Engine->GetMaxClients() + 1); n++) {
		CBaseEntity *ent = gInts.EntityList->GetClientEntity(n);

		if (!ent 
			|| ent == pLocal 
			|| !ent->IsPlayer()
			|| ent->GetTeamNum() == pLocal->GetTeamNum()
			|| ent->IsDormant()
			|| !ent->IsAlive()  
			|| !ent->IsVulnerable()
			|| IgnoreCloaked && ent->IsCloaked()
			|| IgnoreTaunting && ent->IsTaunting())
			continue;

		if (RemoveDisguise)
			ent->RemoveCond(TFCond_Disguised);

		Vec3 ent_pos	= ent->GetHitboxPos(hitbox);
		Vec3 ang_to_ent = Math::CalcAngle(LocalPos, ent_pos);
		float fov		= Math::CalcFov(LocalAngles, ang_to_ent);
		float dist		= ent_pos.DistTo(LocalPos);

		Targets.push_back({ ent, fov, dist, ang_to_ent, ent_pos, LocalPos });
	}

	if (Targets.empty())
		return {}; //if it's empty abort

	std::sort(Targets.begin(), Targets.end(), [&](const Target_t &a, const Target_t &b) -> bool {
		return ((is_melee && AimAtClosest) ? (a.dist < b.dist) : (a.fov < b.fov));
	});

	for (auto &v : Targets)
	{
		int vis_hitbox = -1;
		
		//if the pos is not visible (or if we're aiming at the head but the hitbox is not head) try some corrections
		if (!Utils::Vis_Pos_IdOut(pLocal, v.ptr, v.local_pos, v.ent_pos, vis_hitbox) || (hitbox == HITBOX_HEAD && vis_hitbox != hitbox)) {
			Vec3 pre_correction_ang = v.ang_to_ent;

			//multipoint
			if (hitbox == HITBOX_HEAD)
			{
				if (!Multipoint)
					continue;

				DWORD *model = v.ptr->GetModel();
				if (!model)
					continue;

				studiohdr_t *hdr = reinterpret_cast<studiohdr_t *>(gInts.ModelInfo->GetStudioModel(model));
				if (!hdr)
					continue;

				matrix3x4 bone_matrix[128];
				if (!v.ptr->SetupBones(bone_matrix, 128, 0x100, gInts.Globals->curtime))
					continue;

				mstudiohitboxset_t *set = hdr->GetHitboxSet(v.ptr->GetHitboxSet());
				if (!set)
					continue;

				mstudiobbox_t *box = set->pHitbox(HITBOX_HEAD);
				if (!box)
					continue;

				Vec3 mins = (box->bbmin * 0.85f); //scale them down a bit for accuraccy reasons
				Vec3 maxs = (box->bbmax * 0.85f);

				Vec3 points[5] = {
					Vec3(((mins.x + maxs.x) * 0.5f), ((mins.y + maxs.y) * 0.5f), maxs.z), //top center for aim height meme
					Vec3(maxs.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)), //sides center:
					Vec3(mins.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)),
					Vec3(((mins.x + maxs.x) * 0.5f), maxs.y, ((mins.z + maxs.z) * 0.5f)),
					Vec3(((mins.x + maxs.x) * 0.5f), mins.y, ((mins.z + maxs.z) * 0.5f)),
				};

				Vec3 out[5] = { Vec3() };

				for (int n = 0; n < 5; n++) {
					Math::VectorTransform(points[n], bone_matrix[box->bone], out[n]);
					if (Utils::Vis_Pos_Id(pLocal, v.ptr, v.local_pos, out[n], HITBOX_HEAD)) {
						v.ang_to_ent = Math::CalcAngle(v.local_pos, out[n]); //recalculate
						break;
					}
				}
			}

			//hitscan
			else if (hitbox == HITBOX_PELVIS)
			{
				if (!Hitscan)
					continue;

				for (int n = 1; n < v.ptr->GetNumOfHitboxes(); n++) {
					Vec3 vis_body = v.ptr->GetHitboxPos(n);
					if (Utils::Vis_Pos(pLocal, v.ptr, v.local_pos, vis_body)) {
						v.ang_to_ent = Math::CalcAngle(v.local_pos, vis_body); //recalculate
						break;
					}
				}
			}

			if (v.ang_to_ent.x == pre_correction_ang.x && v.ang_to_ent.y == pre_correction_ang.y)
				continue; //we didn't find a correction, skip this ent
		}

		if (is_melee) {
			if (InRangeOnly && !Utils::CanMeleeHit(wep, v.ang_to_ent, v.ptr->GetIndex()))
				continue;
			
			if (AimAtClosest)
				return v; //remember these are sorted already!
		}

		if (v.fov < AimFov)
			return v;
	}

	return {};
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
		int wep_idx = wep->GetItemDefinitionIndex();

		switch (pLocal->GetClassNum())
		{
			case TF2_Sniper: {
				return (wep_slot == 0 ? HITBOX_HEAD : HITBOX_PELVIS);
			}

			case TF2_Spy: {
				return ((wep_idx == Spy_m_TheAmbassador || wep_idx == Spy_m_FestiveAmbassador) ? HITBOX_HEAD : HITBOX_PELVIS);
			}

			default: return HITBOX_PELVIS;
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

	if (AimTime > 0.0f) {
		cmd->viewangles = SmoothStartAngle;
		float time = std::clamp(((gInts.Globals->curtime - SmoothStartTime) / AimTime), 0.0f, 1.0f);
		Vec3 delta = (target.ang_to_ent - SmoothStartAngle);
		Math::ClampAngles(delta);
		float ease = Math::ExponentialEaseOut(time);
		cmd->viewangles += (delta * ease);
		gInts.Engine->SetViewAngles(cmd->viewangles);
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
	int wep_slot	= wep->GetSlot();
	int wep_idx		= wep->GetItemDefinitionIndex();
	int class_num	= pLocal->GetClassNum();

	if (AimTime > 0.0f)
	{
		//you can check the easing == 1 for this but it's not good
		Vec3 vForward = Vec3();
		Math::AngleVectors(cmd->viewangles, &vForward);
		Vec3 vTraceStart = target.local_pos;
		Vec3 vTraceEnd = (vTraceStart + (vForward * 9999.0f));

		Ray_t ray;
		ray.Init(vTraceStart, vTraceEnd);
		CTraceFilter filter;
		filter.pSkip = pLocal;
		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);

		static float timer = gInts.Globals->curtime;

		if (trace.m_pEnt && trace.m_pEnt->GetIndex() == target.ptr->GetIndex()) {
			if (GetAimHitbox(pLocal, wep) == HITBOX_HEAD && trace.hitbox != HITBOX_HEAD)
				return false;

			if ((gInts.Globals->curtime - timer) < 0.15f)
				return false;
		}

		else {
			timer = gInts.Globals->curtime;
			return false;
		}
	}

	if (class_num == TF2_Spy && wep_slot == 2) {
		if (AimMelee && AutoBackstab) {
			if (Utils::CanMeleeHit(wep, target.ang_to_ent, target.ptr->GetIndex()))
				if (Utils::CanBackstab(cmd->viewangles, target.ptr->GetEyeAngles(), (target.ptr->GetWorldSpaceCenter() - pLocal->GetWorldSpaceCenter())))
					return true;

			return false;
		}
	}

	if (!Autoshoot)
		return false;

	if (wep_slot < 2)
	{
		if (class_num == TF2_Sniper) {
			if (wep_slot == 0 && WaitForHS && pLocal->IsScoped() && !gLocalInfo.CanHeadShot)
				return false;
		}

		else if (class_num == TF2_Spy) {
			if ((wep_idx == Spy_m_TheAmbassador || wep_idx == Spy_m_FestiveAmbassador) && WaitForHS && !gLocalInfo.CanHeadShot)
				return false;
		}
	}

	else if (wep_slot == 2)
		if (AimMelee && !InRangeOnly)
			if (!Utils::CanMeleeHit(wep, target.ang_to_ent, target.ptr->GetIndex()))
				return false;

	return true;
}

bool CAimbot::TargetChanged() {
	static int old_target = gLocalInfo.CurrentTargetIndex;
	if (gLocalInfo.CurrentTargetIndex != old_target) {
		old_target = gLocalInfo.CurrentTargetIndex;
		return true;
	}
	return false;
}

void CAimbot::Run(CBaseEntity *pLocal, CBaseCombatWeapon *pLocalWeapon, CUserCmd *cmd)
{
	gLocalInfo.CurrentTargetIndex = -1;

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
		CProjectileWeapon ProjectileWep(pLocalWeapon);

		if (ProjectileWep.GetWeaponInfo().speed > 0.0f)
		{
			target.ent_pos.z -= 15.0f;

			CLinearPredictor Predictor(target.ent_pos, target.ptr->GetVelocity());
			Solution_t Solution = {};

			if (Solve(target.local_pos, ProjectileWep, Predictor, Solution))
				target.ang_to_ent = { -RAD2DEG(Solution.pitch), RAD2DEG(Solution.yaw), 0.0f };

			else return;
		}

		if (ScopedOnly && (pLocal->GetClassNum() == TF2_Sniper && pLocalWeapon->GetSlot() == 0 && !pLocal->IsScoped())) {
			SmoothStartTime = gInts.Globals->curtime;
			SmoothStartAngle = cmd->viewangles;
			return;
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