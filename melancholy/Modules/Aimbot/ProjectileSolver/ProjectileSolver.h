#pragma once
#include "../../../SDK/SDK.h"

//https://github.com/CasualX/apexbot ty <3

struct ProjectileInfo_t {
	float speed = 0.0f;
	float gravity = 0.0f;
};

class CProjectileWeapon {
private:
	CBaseCombatWeapon *ProjectileWeapon = nullptr;

public:
	inline CProjectileWeapon(CBaseCombatWeapon *wep) : ProjectileWeapon(wep) {};
	ProjectileInfo_t GetWeaponInfo() const;
	Vec3 GetProjectileFireSetup(const Vec3 &origin, const Vec3 &target) const;
};

class CTargetPredictor {
public:
	virtual Vec3 PredictPosition(float time) const = 0;
};

class CLinearPredictor : public CTargetPredictor {
public:
	Vec3 origin = Vec3();
	Vec3 velocity = Vec3();

public:
	inline CLinearPredictor(Vec3 origin, Vec3 velocity) : origin(origin), velocity(velocity) {}
	Vec3 PredictPosition(float time) const override;
};

struct Solution_t {
	float pitch = 0.0f;
	float yaw	= 0.0f;
	float time	= 0.0f;
};

bool Solve(const Vec3 &origin, const CProjectileWeapon &weapon, const CTargetPredictor &target, Solution_t &sol);