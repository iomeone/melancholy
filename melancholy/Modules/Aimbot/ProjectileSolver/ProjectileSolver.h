#pragma once
#include "../../../SDK/SDK.h"

struct ProjectileInfo_t {
	float speed = 0.0f;
	float gravity = 0.0f;
};

class CProjectileWeapon {
private:
	CBaseCombatWeapon *ProjectileWeapon = nullptr;

public:
	CProjectileWeapon(CBaseCombatWeapon *wep);
	ProjectileInfo_t GetWeaponInfo();
};

//TODO