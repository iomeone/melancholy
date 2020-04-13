#pragma once
#include "../../Modules/ESP/ESP.h"

namespace FrameStageNotify
{
	const int Index = 35;
	void __fastcall Hook(PVOID client, int edx, ClientFrameStage_t frame);
}