#pragma once
#include "../../Modules/Misc/Misc.h"
#include "../../Modules/Aimbot/Aimbot.h"

namespace CreateMove {
	const int Index = 21;
	bool __fastcall Hook(void *client_mode, int edx, float input_sample_frametime, CUserCmd *cmd);
}