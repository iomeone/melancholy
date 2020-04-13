#pragma once
#include "../IMaterial/IMaterial.h"

class CModelRender
{
public:
	void ForcedMaterialOverride(IMaterial *mat, OverrideType_t type = OVERRIDE_NORMAL);
	void DrawModelExecute(void *state, ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld);
};