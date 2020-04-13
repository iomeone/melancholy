#pragma once
#include "../../SDK/SDK.h"

namespace RunCommand
{
	const int Index = 17;
	void __fastcall Hook(IPrediction *prediction, int edx, CBaseEntity *entity, CUserCmd *cmd, IMoveHelper *move_helper);
}