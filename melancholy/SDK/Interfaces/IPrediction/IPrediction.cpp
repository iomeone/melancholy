#include "IPrediction.h"

void IPrediction::SetViewAngles(Vec3 &ang)
{
	typedef void(__thiscall *FN)(PVOID, Vec3 &);
	GetVFunc<FN>(this, 14)(this, ang);
}

void IPrediction::SetLocalViewAngles(Vec3 &vAng)
{
	typedef void(__thiscall *FN)(PVOID, Vec3 &);
	GetVFunc<FN>(this, 16)(this, vAng);
}

void IPrediction::RunCommand(CBaseEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper)
{
	typedef void(__thiscall *FN)(PVOID, CBaseEntity *, CUserCmd *, IMoveHelper *);
	GetVFunc<FN>(this, 17)(this, player, ucmd, moveHelper);
}

void IPrediction::SetupMove(CBaseEntity *pEntity, CUserCmd *pCmd, IMoveHelper *pMoveHelper, PVOID pMoveData)
{
	typedef void(__thiscall *FN)(PVOID, CBaseEntity *, CUserCmd *, IMoveHelper *, PVOID);
	GetVFunc<FN>(this, 18)(this, pEntity, pCmd, pMoveHelper, pMoveData);
}

void IPrediction::FinishMove(CBaseEntity *pEntity, CUserCmd *pCmd, PVOID pMoveData)
{
	typedef void(__thiscall *FN)(PVOID, CBaseEntity *, CUserCmd *, PVOID);
	GetVFunc<FN>(this, 19)(this, pEntity, pCmd, pMoveData);
}

void IPrediction::SetIdealPitch(CBaseEntity *player, const Vec3 &origin, const Vec3 &angles, const Vec3 &viewheight)
{
	typedef void(__thiscall *FN)(PVOID, CBaseEntity *, const Vec3 &, const Vec3 &, const Vec3 &);
	GetVFunc<FN>(this, 20)(this, player, origin, angles, viewheight);
}