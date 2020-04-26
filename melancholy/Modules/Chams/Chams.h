#pragma once
#include "../../SDK/SDK.h"

class CChams
{
private:
	enum struct ChamMode_t {
		DEFAULT = -1,
		VISIBLE,
		INVISIBLE,
		ALWAYS
	};

public:
	bool Active	= false;
	float AlphaOverride = 0.1f;

	int PlayerChams			= 2; //0 off 1 shaded 2 flat
	int PlayerChamsMode		= 2; //0 visible 1 invisible 2 always
	bool NoTeammatePlayers	= true;
	bool PlayerCosmetics	= true;
	bool PlayerWeapons		= true;

	int BuildingChams			= 2;
	int BuildingChamsMode		= 2;
	bool NoTeammateBuildings	= true;

	int PickupChams		= 2;
	int PickupChamsMode	= 2;

	void Run();
};

extern CChams gChams;