#include "CModelRender.h"

void CModelRender::ForcedMaterialOverride(IMaterial *mat, OverrideType_t type)
{
	typedef void(__thiscall *FN)(PVOID, IMaterial *, OverrideType_t);
	return GetVFunc<FN>(this, 1)(this, mat, type);
}

void CModelRender::DrawModelExecute(void *state, ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	typedef void(__thiscall *FN)(PVOID, void *, ModelRenderInfo_t &, matrix3x4 *);
	return GetVFunc<FN>(this, 19)(this, state, pInfo, pCustomBoneToWorld);
}