#pragma once
#include "../../SDK/SDK.h"

class CChams {
private:
	enum struct ChamMode_t {
		DEFAULT = -1,
		VISIBLE,
		INVISIBLE,
		ALWAYS
	};

public:
	bool Active	= true;
	float AlphaOverride = 0.2f;

	int PlayerChams			= 2; //0 off 1 shaded 2 flat 3 wireframe
	int PlayerChamsMode		= 1; //0 visible 1 invisible 2 always
	int PlayerChamsColor	= 0; //0 team 1 health 2 caramelldansen
	bool NoTeammatePlayers	= true;
	bool PlayerCosmetics	= true;
	bool PlayerWeapons		= true;

	int BuildingChams			= 2;
	int BuildingChamsMode		= 1;
	int BuildingChamsColor		= 0; //0 team 1 health 2 caramelldansen
	bool NoTeammateBuildings	= true;

	int PickupChams		= 1;
	int PickupChamsMode	= 2;
	int PickupChamsColor = 0; //0 pickup 1 caramelldansen

	void Run();
};

extern CChams gChams;