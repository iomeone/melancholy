#include "ProjectileSolver.h"

//-------------------------------------------------- CProjectileWeapon

ProjectileInfo_t CProjectileWeapon::GetWeaponInfo() const {
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

	return { out.speed, (out.gravity * 800.0f) + 0.01f }; //need + 0.01f to get non gravity affected weapons to work
}

Vec3 CProjectileWeapon::GetProjectileFireSetup(const Vec3 &origin, const Vec3 &target) const { return (target - origin); }

//-------------------------------------------------- CLinearPredictor

Vec3 CLinearPredictor::PredictPosition(float time) const { return (origin + velocity * time); }

//-------------------------------------------------- Solver

bool Optimal(float x, float y, float v0, float g, float &pitch)
{
	const float root = v0 * v0 * v0 * v0 - g * (g * x * x + 2.0f * y * v0 * v0);

	if (root < 0.0f)
		return false;

	pitch = atan((v0 * v0 - sqrt(root)) / (g * x));

	return true;
}

static bool Solve2D(const Vec3 &origin, const CProjectileWeapon &weapon, const Vec3 &target, Solution_t &sol)
{
	const auto v	= weapon.GetProjectileFireSetup(origin, target);
	const float dx	= sqrt(v.x * v.x + v.y * v.y);
	const float dy	= v.z;
	const float v0	= weapon.GetWeaponInfo().speed;
	const float g	= weapon.GetWeaponInfo().gravity;

	if (!Optimal(dx, dy, v0, g, sol.pitch))
		return false;

	sol.time = dx / (cos(sol.pitch) * v0);
	sol.yaw = atan2(v.y, v.x);

	return true;
}

bool Solve(const Vec3 &origin, const CProjectileWeapon &weapon, const CTargetPredictor &target, Solution_t &sol)
{
	static const float MAX_TIME = 1.0f;
	static const float TIME_STEP = 1.0 / 256.0f;

	for (float target_time = 0.0f; target_time <= MAX_TIME; target_time += TIME_STEP) {
		const auto target_pos = target.PredictPosition(target_time);

		if (!Solve2D(origin, weapon, target_pos, sol))
			return false;

		if (sol.time < target_time)
			return true;
	}

	return false;
}