#pragma once
#include "../ESP/ESP.h"

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

	int PlayerChams			= 0; //0 off 1 shaded 2 flat
	int PlayerChamsMode		= 1; //0 visible 1 invisible 2 always
	bool NoTeammatePlayers	= true;

	int BuildingChams			= 0;
	int BuildingChamsMode		= 1;
	bool NoTeammateBuildings	= true;

	int PickupChams		= 1;
	int PickupChamsMode	= 2;

	void Run();
};

extern CChams gChams;