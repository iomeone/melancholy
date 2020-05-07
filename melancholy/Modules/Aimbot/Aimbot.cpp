#include "Aimbot.h"

Vec3 SmoothStartAngle	= Vec3();
float SmoothStartTime	= 0.0f;
bool AimFinished		= false;	//used for projectile autoshoot
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

	if (CorrectionMethod == 0)
	{
		std::sort(Targets.begin(), Targets.end(), [&](const Target_t &a, const Target_t &b) -> bool {
			return ((is_melee && AimAtClosest) ? (a.dist < b.dist) : (a.fov < b.fov));
		});

		for (auto &v : Targets)
		{
			if (!CorrectAimPos(pLocal, wep, cmd, v))
				continue;

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
	}

	else if (CorrectionMethod == 1)
	{
		//CONS: since at this stage we only have one target,
		//		returning here means not aiming at anyone else
		//PROS: very cheap to do as we do all the correction checks for 1 entity only (the one closest to us or the closest to the fov)

		Target_t out = *std::min_element(Targets.begin(), Targets.end(), [&](const Target_t &a, const Target_t &b) -> bool {
			return ((is_melee && AimAtClosest) ? (a.dist < b.dist) : (a.fov < b.fov));
		});

		if (!CorrectAimPos(pLocal, wep, cmd, out))
			return {};

		if (is_melee)
		{
			if (InRangeOnly && !Utils::CanMeleeHit(wep, out.ang_to_ent, out.ptr->GetIndex()))
				return {};

			if (AimAtClosest)
				return out;
		}

		if (out.fov < AimFov)
			return out;
	}

	return {};
}

bool CAimbot::CorrectAimPos(CBaseEntity *pLocal, CBaseCombatWeapon *wep, CUserCmd *cmd, Target_t &target)
{
	bool IsTargetPlayer = target.ptr->IsPlayer();

	CProjectileWeapon ProjectileWep(wep);
	ProjectileInfo_t ProjectileInfo = ProjectileWep.GetWeaponInfo();

	//don't we also want multipoint with projectiles :thinking:
	//I guess not, for now
	if (ProjectileInfo.speed > 0.0f)
	{
		if (!ProjectileAim)
			return false;

		int local_class			 = pLocal->GetClassNum();
		Vec3 target_velocity	 = (IsTargetPlayer ? target.ptr->GetVelocity() : Vec3(0.0f, 0.0f, 0.0f));
		Vec3 target_acceleration = (IsTargetPlayer ? Vec3(0.0f, 0.0f, 800.0f) : Vec3(0.0f, 0.0f, 0.0f));
		bool target_onground	 = (IsTargetPlayer ? target.ptr->IsOnGround() : true);

		if (local_class == TF2_Demoman) {
			/*Vec3 vecForward = Vec3(), vecRight = Vec3(), vecUp = Vec3();
			Math::AngleVectors(cmd->viewangles, &vecForward, &vecRight, &vecUp);
			target.local_pos += ((vecForward * 16.0f) + (vecRight * 8.0f) + (vecUp * -6.0f));*/
			target.ent_pos.z -= (IsTargetPlayer ? (!target_onground && target_velocity.z < 0.0f ? 50.0f : 30.0f) : 3.0f);
		}

		else if (local_class == TF2_Soldier) {
			target.ent_pos.z -= (IsTargetPlayer ? 30.0f : 0.0f);
		}

		CPredictor Predictor(target.ent_pos, target_velocity, target_acceleration, target.ptr);
		Solution_t Solution = {};

		if (!Solve(target.local_pos, ProjectileWep, Predictor, Solution, target_onground))
			return false;

		target.ang_to_ent = { -RAD2DEG(Solution.pitch), RAD2DEG(Solution.yaw), 0.0f };

		//post pred corrections
		if (local_class == TF2_Demoman && IsTargetPlayer) {
			//Idk how to correct pipes :(
			Vec3 vecForward = Vec3(), vecRight = Vec3(), vecUp = Vec3();
			Math::AngleVectors(target.ang_to_ent, &vecForward, &vecRight, &vecUp);
			Vec3 vecVelocity = ((vecForward * ProjectileInfo.speed) - (vecUp * 50.0f));
			Math::VectorAngles(vecVelocity, target.ang_to_ent);

			//the game launches the pipes with ((vecForward * ProjectileInfo.speed) + (vecUp * 200.0f));
			//but correcting the final angles with ((vecForward * ProjectileInfo.speed) - (vecUp * 200.0f)); doesn't do much good
			//so just using (- (up * 50)) atm, the results are still far from desirable,
			//but I think the solver itself has something to do with it
		}

		target.fov = Math::CalcFov(cmd->viewangles, target.ang_to_ent);
	}

	else
	{
		if (IsTargetPlayer)
		{
			int hitbox = GetAimHitbox(pLocal, wep);
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

					Vec3 mins = (box->bbmin * MpScale);
					Vec3 maxs = (box->bbmax * MpScale);

					//I hope these are what I think they are lmao
					Vec3 points[5] = {
						Vec3(((mins.x + maxs.x) * 0.5f), ((mins.y + maxs.y) * 0.5f), maxs.z), //top center
						Vec3(maxs.x, ((mins.y + maxs.y) * 0.5f), ((mins.z + maxs.z) * 0.5f)), //sides center
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
				else if (hitbox == HITBOX_PELVIS || hitbox == HITBOX_BODY)
				{
					if (!Hitscan)
						return false;

					for (int n = (HitscanSkipHead ? 1 : 0); n < target.ptr->GetNumOfHitboxes(); n++)
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

		else
		{
			Ray_t ray;
			ray.Init(target.local_pos, target.ent_pos);
			CTraceFilter filter;
			filter.pSkip = target.ptr;
			CGameTrace trace;
			gInts.EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);

			if (trace.fraction < 0.99f)
			{
				if (!Multipoint)
					return false;

				matrix3x4 &transform = target.ptr->GetRgflCoordinateFrame(); //not sure if this is the right way to do this

				CObject *building = reinterpret_cast<CObject *>(target.ptr);

				if (!building)
					return false;

				float scale = ((building->GetLevel() < 2 && building->GetClassId() == CObjectSentrygun) ? 0.70f : 0.85f); //0.85f was missing on lvl 1 sentry
				Vec3 mins = (target.ptr->GetCollideableMins() * scale); //we can have these quite high because buildings don't move
				Vec3 maxs = (target.ptr->GetCollideableMaxs() * scale);

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

					ray.Init(target.local_pos, out[n]);
					filter.pSkip = target.ptr;
					gInts.EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);

					if (trace.fraction > 0.98f)
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

				return false;
			}
		}
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

		switch (pLocal->GetClassNum())
		{
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
		float time = std::clamp(((gInts.Globals->curtime - SmoothStartTime) / AimTime), 0.0f, 1.0f);
		AimFinished = (time > 0.99f);

		cmd->viewangles = SmoothStartAngle;
		Vec3 delta = (target.ang_to_ent - SmoothStartAngle);
		Math::ClampAngles(delta);

		float method = 0.0f;

		//more @ https://easings.net // https://github.com/acron0/Easings/blob/master/Easings.cs 
		switch (AimMethod) {
			case 0: { method = time; break; }
			case 1: { method = Math::ExponentialEaseOut(time); break; }
			case 2: { method = Math::ExponentialEaseIn(time); break; }
			case 3: { method = Math::QuadraticEaseInOut(time); break; }
		}

		cmd->viewangles += (delta * method);
		gInts.Engine->SetViewAngles(cmd->viewangles);
	}

	else
	{
		if (Silent)
		{
			Utils::FixSilentMovement(cmd, target.ang_to_ent);
			cmd->viewangles = target.ang_to_ent;
		}

		else
		{
			cmd->viewangles = target.ang_to_ent;
			gInts.Engine->SetViewAngles(target.ang_to_ent);
		}
	}
}

bool CAimbot::ShouldAutoshoot(CBaseEntity *pLocal, CBaseCombatWeapon *wep, Target_t &target, CUserCmd *cmd)
{
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

	//I think it's more logical to do ray checking after the cheaper checks pass

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
				gInts.EngineTrace->TraceRay(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);

				static float timer = gInts.Globals->curtime;

				//if we're already on a target, shoot even if aim (smooth) hasn't finished
				if (trace.m_pEnt && trace.m_pEnt->GetIndex() == target.ptr->GetIndex())
				{
					if (target.ptr->IsPlayer()) {
						if (GetAimHitbox(pLocal, wep) == HITBOX_HEAD && trace.hitbox != HITBOX_HEAD)
							return false;
					}

					if ((gInts.Globals->curtime - timer) < 0.065f) //wait a bit so we don't shoot the very edge of the hitbox
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

	return true;
}

bool CAimbot::TargetChanged()
{
	static int old_target = gLocalInfo.CurrentTargetIndex;

	if (gLocalInfo.CurrentTargetIndex != old_target) {
		old_target = gLocalInfo.CurrentTargetIndex;
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
		|| gInts.Engine->Con_IsVisible()
		|| gInts.EngineVGui->IsGameUIVisible())
		return;

	if (!AimMelee && pLocalWeapon->GetSlot() == 2)
		return;

	Target_t target = GetTarget(pLocal, pLocalWeapon, cmd);

	if (target.ptr)
	{
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