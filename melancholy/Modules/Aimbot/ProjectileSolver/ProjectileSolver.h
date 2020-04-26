#pragma once
#include "../../../SDK/SDK.h"

struct ProjectileInfo_t {
	float speed		= 0.0f;
	float gravity	= 0.0f;
	bool is_pipe	= false;
};

class CProjectileWeapon {
private:
	CBaseCombatWeapon *ProjectileWeapon = nullptr;

public:
	CProjectileWeapon(CBaseCombatWeapon *wep);
	ProjectileInfo_t GetWeaponInfo() const;
};

class CPredictor {
public:
	Vec3 origin			= Vec3();
	Vec3 velocity		= Vec3();
	Vec3 gravity		= Vec3();
	CBaseEntity *ptr	= nullptr;

public:
	inline CPredictor(Vec3 origin, Vec3 velocity, Vec3 acceleration, CBaseEntity *ptr) : origin(origin), velocity(velocity), gravity(acceleration), ptr(ptr){}
	Vec3 PredictPosition(float time, const Vec3 &pos, const Vec3 &vel, const Vec3 &accel, bool on_ground) const;
};

struct Solution_t {
	float pitch				= 0.0f;
	float yaw				= 0.0f;
	float time				= 0.0f;
	bool ray_hit_ground		= false;
	bool ray_hit_ceiling	= false;
};

struct PredOut_t {
	Vec3 pred_pos = Vec3();
	Vec3 non_pred_pos = Vec3();
}; extern PredOut_t gPredOut;

bool Solve(const Vec3 &origin, const CProjectileWeapon &weapon, const CPredictor &target, Solution_t &sol, bool on_ground);