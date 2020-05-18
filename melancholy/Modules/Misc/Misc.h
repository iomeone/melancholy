#pragma once
#include "../../SDK/SDK.h"

class CMisc
{
private:
	void Bhop(CBaseEntity *pLocal, CUserCmd *cmd);

public:
	bool Bunnyhop = true;
	ConVar *cheats = nullptr;
	int timescale = 1;

	void Run(CBaseEntity *pLocal, CUserCmd *cmd);
};

extern CMisc gMisc;