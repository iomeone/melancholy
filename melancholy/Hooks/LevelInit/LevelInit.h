#pragma once
#include "../../SDK/SDK.h"

namespace LevelInit {
	const int PreIndex		= 5;
	const int PostIndex		= 6;
	const int ShutdownIndex = 7;

	void __fastcall LevelInitPreEntity(void *chl_client, int edx, char const *pMapName);
	void __fastcall LevelInitPostEntity(void *chl_client, int edx);
	void __fastcall LevelShutdown(void *chl_client, int edx);
}