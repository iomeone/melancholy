#include "ProjectileSolver.h"

//credits to https://github.com/CasualX

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
		//soldier
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
			out = { 1100, 0.0f };
			break;
		}

		case Soldier_m_TheDirectHit: {
			out = { 1980.0f, 0.0f };
			break;
		}

		case Soldier_m_TheLibertyLauncher: {
			out = { 1500.0f, 0.0f };
			break;
		}

		//demoman
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
			out = { 1200.0f, 0.4f };
			break;
		}

		case Demoman_m_TheLooseCannon: {
			out = { 1400.0f, 0.4f };
			break;
		}

		case Demoman_m_TheLochnLoad: {
			out = { 1500.0f, 0.4f };
			break;
		}
	}

	return out;
}

Vec3 CProjectileWeapon::GetProjectileFireSetup(const Vec3 &origin, const Vec3 &target) const { return (target - origin); }

//-------------------------------------------------- CPredictor

Vec3 CPredictor::PredictPosition(float time, const Vec3 &pos, const Vec3 &vel, const Vec3 &accel, bool on_ground) const {
	return (on_ground ? (pos + (vel * time)) : (pos  + (vel * time) - accel * time * time * 0.5f));
}

//-------------------------------------------------- Solver

bool Optimal(float x, float y, float v0, float g, float &pitch) {
	const float root = v0 * v0 * v0 * v0 - g * (g * x * x + 2.0f * y * v0 * v0);

	if (root < 0.0f)
		return false;

	pitch = atan((v0 * v0 - sqrt(root)) / (g * x));

	return true;
}

bool Solve2D(const Vec3 &origin, const CProjectileWeapon &weapon, const Vec3 &target, Solution_t &sol) {
	const auto v	= weapon.GetProjectileFireSetup(origin, target);
	const float dx	= sqrt(v.x * v.x + v.y * v.y);
	const float dy	= v.z;
	const float v0	= weapon.GetWeaponInfo().speed;
	const float g	= (800.0f * weapon.GetWeaponInfo().gravity);

	if (!Optimal(dx, dy, v0, (g <= 0.0f ? 0.1f : g), sol.pitch))
		return false;

	sol.time = dx / (cos(sol.pitch) * v0);
	sol.yaw = atan2(v.y, v.x);

	return true;
}

bool Solve(const Vec3 &origin, const CProjectileWeapon &weapon, const CPredictor &target, Solution_t &sol, bool on_ground)
{
	static const float MAX_TIME = 1.0f;
	static const float TIME_STEP = 1.0f / 256.0f;

	for (float target_time = 0.0f; target_time <= MAX_TIME; target_time += TIME_STEP)
	{
		Vec3 target_pos = target.PredictPosition(target_time, target.origin, target.velocity, target.acceleration, on_ground);

		Ray_t ray;
		ray.Init(target.origin, target_pos);
		CTraceFilter filter;
		filter.pSkip = target.ptr;
		CGameTrace trace;
		gInts.EngineTrace->TraceRay(ray, MASK_PLAYERSOLID, &filter, &trace);

		if (!trace.endpos.IsZero())
			target_pos = trace.endpos;

		if (!Solve2D(origin, weapon, target_pos, sol))
			return false;

		if (sol.time < target_time)
			return true;
	}

	return false;
}