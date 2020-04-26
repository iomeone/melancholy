#pragma once
#include "../../SDK/SDK.h"

class CGlow {
public:
	bool Active = false;
	float GlowAlpha = 0.9f;

	int PlayerGlow				= 1; //0 off 1 team 2 health
	bool NoTeammatePlayers		= true;

	int BuildingGlow			= 1;
	bool NoTeammateBuildings	= true;

	void Run(CBaseEntity *pLocal, ClientFrameStage_t frame);
};

extern CGlow gGlow;