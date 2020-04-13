#pragma once
#include "../../Defines.h"

class CModelInfo
{
public:
	const char *GetModelName(DWORD *model);
	void GetModelRenderBounds(const DWORD *model, Vec3 &mins, Vec3 &maxs);
	DWORD *GetStudioModel(DWORD *model);
};