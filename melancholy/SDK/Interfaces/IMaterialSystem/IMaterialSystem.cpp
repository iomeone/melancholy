#include "IMaterialSystem.h"

IMaterial *IMaterialSystem::FindMaterial(char const *pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix)
{
	typedef IMaterial *(__thiscall *FN)(PVOID, const char *, const char *, bool, const char *);
	return GetVFunc<FN>(this, 73)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
}

IMaterial *IMaterialSystem::CreateMaterial(char const *pMaterialName, KeyValues *kv)
{
	typedef IMaterial *(__thiscall *FN)(PVOID, const char *, KeyValues *);
	return GetVFunc<FN>(this, 72)(this, pMaterialName, kv);
}

IMaterial *IMaterialSystem::GetMaterial(MaterialHandle_t h)
{
	typedef IMaterial *(__thiscall *FN)(PVOID, MaterialHandle_t);
	return GetVFunc<FN>(this, 78)(this, h);
}

MaterialHandle_t IMaterialSystem::FirstMaterial()
{
	typedef MaterialHandle_t(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 75)(this);
}

MaterialHandle_t IMaterialSystem::InvalidMaterial()
{
	typedef MaterialHandle_t(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 77)(this);
}

MaterialHandle_t IMaterialSystem::NextMaterial(MaterialHandle_t h)
{
	typedef MaterialHandle_t(__thiscall *FN)(PVOID, MaterialHandle_t);
	return GetVFunc<FN>(this, 76)(this, h);
}