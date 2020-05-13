#pragma once
#include "../../SDK/SDK.h"

class CGlow {
public:
	bool Active = true;
	float GlowAlpha = 1.0f;

	int PlayerGlow				= 2; //0 off 1 team 2 health 3 caramelldansen
	bool NoTeammatePlayers		= true;

	int BuildingGlow			= 2;
	bool NoTeammateBuildings	= true;

	void Run(CBaseEntity *pLocal, ClientFrameStage_t frame);
};

extern CGlow gGlow;