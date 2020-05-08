#include "ProjectileSolver.h"

//credits to Casual_Hacker

//-------------------------------------------------- CProjectileWeapon

CProjectileWeapon::CProjectileWeapon(CBaseCombatWeapon *wep) {
	ProjectileWeapon = wep;
}

ProjectileInfo_t CProjectileWeapon::GetWeaponInfo() const
{
	if (!ProjectileWeapon)
		return {};

	ProjectileInfo_t out = {};

	switch (ProjectileWeapon->GetItemDefinitionIndex())
	{
		case Soldier_m_RocketLauncher:
		case Soldier_m_RocketLauncherR:
		case Soldier_m_TheBlackBox:
		case Soldier_m_TheCowMangler5000:
		case Soldier_m_TheOriginal:
		case Soldier_m_FestiveRocketLauncher:
		case Soldier_m_TheBeggarsBazooka:
		case Soldier_m_SilverBotkillerRocketLauncherMkI:
		case Soldier_m_GoldBotkillerRocketLauncherMkI:
		case Soldier_m_RustBotkillerRocketLauncherMkI:
		case Soldier_m_BloodBotkillerRocketLauncherMkI:
		case Soldier_m_CarbonadoBotkillerRocketLauncherMkI:
		case Soldier_m_DiamondBotkillerRocketLauncherMkI:
		case Soldier_m_SilverBotkillerRocketLauncherMkII:
		case Soldier_m_GoldBotkillerRocketLauncherMkII:
		case Soldier_m_FestiveBlackBox:
		case Soldier_m_TheAirStrike:
		case Soldier_m_WoodlandWarrior:
		case Soldier_m_SandCannon:
		case Soldier_m_AmericanPastoral:
		case Soldier_m_SmalltownBringdown:
		case Soldier_m_ShellShocker:
		case Soldier_m_AquaMarine:
		case Soldier_m_Autumn:
		case Soldier_m_BlueMew:
		case Soldier_m_BrainCandy:
		case Soldier_m_CoffinNail:
		case Soldier_m_HighRollers:
		case Soldier_m_Warhawk: {
			out = { 1100.0f, 0.0f };
			break;
		}

		case Soldier_m_TheDirectHit: {
			out = { 1980.0f, 0.0f};
			break;
		}

		case Soldier_m_TheLibertyLauncher: {
			out = { 1540.0f, 0.0f };
			break;
		}

		case Demoman_m_GrenadeLauncher:
		case Demoman_m_GrenadeLauncherR:
		case Demoman_m_FestiveGrenadeLauncher:
		case Demoman_m_TheIronBomber:
		case Demoman_m_Autumn:
		case Demoman_m_MacabreWeb:
		case Demoman_m_Rainbow:
		case Demoman_m_SweetDreams:
		case Demoman_m_CoffinNail:
		case Demoman_m_TopShelf:
		case Demoman_m_Warhawk:
		case Demoman_m_ButcherBird: {
			out = { 1217.0f, 0.4f }; //1216.6f in the wiki, 1200.0f in the game code :thinking:
			break;
		}

		case Soldier_s_TheRighteousBison:
		case Engi_m_ThePomson6000: {
			out = { 1200.0f, 0.0f };
			break;
		}

		case Demoman_m_TheLooseCannon: {
			out = { 1453.9f, 0.4f };
			break;
		}

		case Demoman_m_TheLochnLoad: {
			out = { 1513.3f, 0.4f };
			break;
		}

		case Engi_m_TheRescueRanger:
		case Medic_m_FestiveCrusadersCrossbow:
		case Medic_m_CrusadersCrossbow: {
			out = { 2400.0f, 0.2f };
			break;
		}

		case Pyro_m_DragonsFury: {
			out = { 3000.0f, 0.0f };
			break;
		}

		case Pyro_s_TheDetonator:
		case Pyro_s_TheFlareGun:
		case Pyro_s_FestiveFlareGun:
		case Pyro_s_TheScorchShot: {
			out = { 2000.0f, 0.2f };
			break;
		}
		case Pyro_s_TheManmelter: {
			out = { 3000.0f, 0.2f };
			break;
		}

		case Medic_m_SyringeGun:
		case Medic_m_SyringeGunR:
		case Medic_m_TheBlutsauger:
		case Medic_m_TheOverdose: {
			out = { 1000.0f, 0.2f };
			break;
		}

		case Sniper_m_TheHuntsman:
		case Sniper_m_FestiveHuntsman:
		case Sniper_m_TheFortifiedCompound: {
			float charge = (gInts.Globals->curtime - ProjectileWeapon->GetChargeTime());
			out = { ((fminf(fmaxf(charge, 0.0f), 1.0f) * 800.0f) + 1800.0f), ((fminf(fmaxf(charge, 0.0f), 1.0f) * -0.4f) + 0.5f) };
			break;
		}
	}

	return out;
}

//-------------------------------------------------- CPredictor

Vec3 CPredictor::PredictPosition(float time, const Vec3 &pos, const Vec3 &vel, const Vec3 &accel, bool on_ground) const {
	return (on_ground ? (pos + (vel * time)) : (pos + (vel * time) - accel * 0.5f * time * time + std::max(1.0f, time * 0.4f)));
}

//-------------------------------------------------- Solver

bool Optimal(float x, float y, float v0, float g, float &pitch)
{
	const float root = v0 * v0 * v0 * v0 - g * (g * x * x + 2.0f * y * v0 * v0);

	if (root < 0.0f) //if it's negative there are no solutions
		return false;

	pitch = atan((v0 * v0 - sqrt(root)) / (g * x));
	return true;
}

bool Solve2D(const Vec3 &origin, const CProjectileWeapon &weapon, const Vec3 &target, Solution_t &sol)
{
	const Vec3 v	= (target - origin);
	const float dx	= sqrt(v.x * v.x + v.y * v.y);
	const float v0	= weapon.GetWeaponInfo().speed;
	const float g	= (800.0f * weapon.GetWeaponInfo().gravity);

	if (g > 0.0f) 
	{
		const float dy = v.z;

		if (!Optimal(dx, dy, v0, g, sol.pitch))
			return false;

		sol.yaw = atan2(v.y, v.x);
	}
	
	else
	{
		Vec3 ang = Math::CalcAngle(origin, target);
		sol.pitch = -DEG2RAD(ang.x);
		sol.yaw = DEG2RAD(ang.y);
	}

	sol.time = dx / (cos(sol.pitch) * v0);
	return true;
}

bool Solve(const Vec3 &origin, const CProjectileWeapon &weapon, const CPredictor &target, Solution_t &sol, bool on_ground)
{
	static const float MAX_TIME = 1.5f;
	static const float TIME_STEP = (MAX_TIME / 256.0f);

	Ray_t ray;
	CGameTrace trace;
	CTraceFilterNoPlayers filter;
	filter.pSkip = target.ptr;

	INetChannelInfo *net_chan = reinterpret_cast<INetChannelInfo *>(gInts.Engine->GetNetChannelInfo());
	static ConVar *cl_interp = gInts.ConVars->FindVar("cl_interp");

	for (float target_time = 0.0f; target_time <= MAX_TIME; target_time += TIME_STEP)
	{
		float interp	= cl_interp->GetFloat();
		float latency	= (net_chan->GetLatency(FLOW_OUTGOING) + net_chan->GetLatency(FLOW_INCOMING));
		float time		= (interp + latency + target_time);

		Vec3 predicted_pos = target.PredictPosition(time, target.origin, target.velocity, target.gravity, on_ground);

		ray.Init(target.origin, predicted_pos);
		gInts.EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

		if (trace.DidHit())
			predicted_pos.z = (trace.endpos.z + (target.ptr->GetViewOffset().z * 0.5f));

		if (!Solve2D(origin, weapon, predicted_pos, sol))
			return false;

		if (sol.time < target_time)
		{
			ray.Init(predicted_pos, origin);
			gInts.EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

			if (trace.fraction < 0.99f)
				return false;

			gLocalInfo.PredStart = target.origin;
			gLocalInfo.PredEnd = predicted_pos;

			return true;
		}
	}

	return false;
}