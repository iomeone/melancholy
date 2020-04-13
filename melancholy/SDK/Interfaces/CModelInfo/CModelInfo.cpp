#include "CModelInfo.h"

const char *CModelInfo::GetModelName(DWORD *model)
{
	typedef const char *(__thiscall *FN)(PVOID, DWORD *);
	return GetVFunc<FN>(this, 3)(this, model);
}

void CModelInfo::GetModelRenderBounds(const DWORD *model, Vec3 &mins, Vec3 &maxs)
{
	typedef void(__thiscall *FN)(PVOID, const DWORD *, Vec3 &, Vec3 &);
	return GetVFunc<FN>(this, 7)(this, model, mins, maxs);
}

DWORD *CModelInfo::GetStudioModel(DWORD *model)
{
	typedef DWORD *(__thiscall *FN)(PVOID, DWORD *);
	return GetVFunc<FN>(this, 28)(this, model);
}