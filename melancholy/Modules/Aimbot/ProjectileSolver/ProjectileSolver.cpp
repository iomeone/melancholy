#include "ProjectileSolver.h"

//-------------------------------------------------- CProjectileWeapon

CProjectileWeapon::CProjectileWeapon(CBaseCombatWeapon *wep) {
	ProjectileWeapon = wep;
}

ProjectileInfo_t CProjectileWeapon::GetWeaponInfo()
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