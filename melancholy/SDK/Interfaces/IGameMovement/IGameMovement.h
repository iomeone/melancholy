#pragma once
#include "../../Defines.h"

class IGameMovement
{
public:
	virtual ~IGameMovement(void) { }
	virtual void ProcessMovement(CBaseEntity *pPlayer, void *pMove) = 0;
	virtual void StartTrackPredictionErrors(CBaseEntity *pPlayer) = 0;
	virtual void FinishTrackPredictionErrors(CBaseEntity *pPlayer) = 0;
	virtual void DiffPrint(char const *fmt, ...) = 0;
	virtual Vec3 GetPlayerMins(bool ducked) const = 0;
	virtual Vec3 GetPlayerMaxs(bool ducked) const = 0;
	virtual Vec3 GetPlayerViewOffset(bool ducked) const = 0;
};