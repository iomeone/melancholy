#pragma once
#include "../Aimbot/Aimbot.h"

enum struct ESPEntType_t {
	DEFAULT = -1,
	PLAYER,
	BUILDING,
	PICKUP
};

struct ESPEnt_t {
	ESPEntType_t type = ESPEntType_t::DEFAULT;
	CBaseEntity *ptr = nullptr;
	float dist = FLT_MAX;
};

struct Spectator_t {
	std::string name = "";
	std::string mode = "";
};

class CESP
{
private:
	const int FontTall = 12;
	const int FontTallSmall = 11;

private:
	std::vector<ESPEnt_t> Entities;

	bool GetEntities(CBaseEntity *pLocal);
	bool GetEntityBoundsW2S(ESPEnt_t &ent, int &x_out, int &y_out, int &w_out, int &h_out);
	RGBA_t GetEntityColor(ESPEnt_t &ent);

public:
	RGBA_t ColTarget	{ 255, 200, 0, 255 };
	RGBA_t ColInvuln	{ 60, 100, 130, 255 };
	RGBA_t ColWhite		{ 255, 255, 255, 255 };
	RGBA_t ColGreen		{ 0, 255, 0, 255 };
	RGBA_t ColOutline	{ 0, 0, 0, 200 };

	//-------------------------------------------------- main
	bool Active		= false;
	bool Players	= true;
	bool Buildings	= true;
	bool Pickups	= true;

	//-------------------------------------------------- local
	bool SpectatorList	= true;
	bool Thirdperson	= false;
	bool NoScope		= true;
	bool NoZoom			= true;
	int CustomFOV		= 110;

	//-------------------------------------------------- players
	int PlayerTextPos		= 0;	//0 top right 1 left bottom 2 center
	bool NoTeammatePlayers	= true;
	bool IgnoreCloaked		= false;
	bool PlayerName			= true;
	bool PlayerHealth		= false;
	int PlayerHealthBar		= 1;	//0 off 1 vertical 2 horizontal
	bool PlayerClass		= true;
	bool PlayerCond			= true;
	bool PlayerBox			= false;
	int PlayerBones			= 0;	//0 off 1 esp 2 white

	//-------------------------------------------------- buildings
	int BuildingTextPos			= 2;	//0 top right 1 left bottom 2 center
	bool NoTeammateBuildings	= true;
	bool BuildingName			= true;
	bool BuildingHealth			= false;
	int BuildingHealthBar		= 2;	//0 off 1 vertical 2 horizontal
	bool BuildingCond			= true;
	bool BuildingBox			= false;

	//-------------------------------------------------- pickups
	bool PickupName		= false;

	void Run();

	std::vector<Spectator_t> Spectators;
};

extern CESP gESP;