#pragma once
#include "ProjectileSolver/ProjectileSolver.h"

class CAimbot
{
private:
	struct Target_t {
		CBaseEntity *ptr	= nullptr;
		float fov			= FLT_MAX;
		float dist			= FLT_MAX;
		Vec3 ang_to_ent		= Vec3();
		Vec3 ent_pos		= Vec3();
		Vec3 local_pos		= Vec3();
	};

	std::vector<Target_t> Targets;

	Target_t GetTarget(CBaseEntity *pLocal, CBaseCombatWeapon *wep, CUserCmd *cmd);
	bool CorrectAimPos(CBaseEntity *pLocal, CBaseCombatWeapon *wep, CUserCmd *cmd, Target_t &target);
	int GetAimHitbox(CBaseEntity *pLocal, CBaseCombatWeapon *wep);
	bool IsAimKeyDown();
	void SetAngles(CBaseEntity *pLocal, Target_t &target, CUserCmd *cmd);
	bool ShouldAutoshoot(CBaseEntity *pLocal, CBaseCombatWeapon *wep, Target_t &target, CUserCmd *cmd);
	bool TargetChanged();

public:
	//main
	bool Active			= true;
	bool Silent			= false;
	bool Autoshoot		= false;
	int AimKey			= 0; //0 lshift 1 lbutton
	float AimFov		= 45.0f;

	//hitscan
	bool WaitForHS	= true;
	bool ScopedOnly = false;

	//melee
	bool AimMelee		= true;
	bool InRangeOnly	= true;
	bool AimAtClosest	= true;
	bool AutoBackstab	= false;

	//players
	int AimHitbox			= 2; //0 head 1 body 2 auto
	bool IgnoreCloaked		= false;
	bool IgnoreTaunting		= true;
	bool RemoveDisguise		= false;

	//buildings
	bool AimSentry		= true;
	bool AimDispenser	= true;
	bool AimTeleporter	= true;

	//smoothing
	float AimTime	= 0.0f;
	int AimMethod	= 0;	//0 time 1 out expo 2 in expo 3 in out quad

	//corrections
	int CorrectionMethod	= 0; //0 expensive 1 cheap

	bool Multipoint			= true;
	float MpScale			= 0.75f;

	bool Hitscan			= true;
	bool HitscanSkipHead	= true;

	bool ProjectileAim		= false;


	void Run(CBaseEntity *pLocal, CBaseCombatWeapon *pLocalWeapon, CUserCmd *cmd);
};

extern CAimbot gAimbot;