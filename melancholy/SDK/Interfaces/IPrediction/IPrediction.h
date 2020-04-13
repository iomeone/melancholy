#pragma once
#include "../IMoveHelper/IMoveHelper.h"

class IPrediction
{
public:
	void SetViewAngles(Vec3 &ang);
	void SetLocalViewAngles(Vec3 &vAng);
	void RunCommand(CBaseEntity *player, CUserCmd *ucmd, IMoveHelper *moveHelper);
	void SetupMove(CBaseEntity *pEntity, CUserCmd *pCmd, IMoveHelper *pMoveHelper, PVOID pMoveData);
	void FinishMove(CBaseEntity *pEntity, CUserCmd *pCmd, PVOID pMoveData);
	void SetIdealPitch(CBaseEntity *player, const Vec3 &origin, const Vec3 &angles, const Vec3 &viewheight);
};