#pragma once
#include "../../Modules/ESP/ESP.h"

namespace OverrideView
{
	const int Index = 16;
	void __fastcall Hook(void *pClientMode, int edx, CViewSetup *pViewSetup);
}