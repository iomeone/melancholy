#pragma once
#include "../IMaterial/IMaterial.h"

class KeyValues; //forward

class IMaterialSystem 
{
public:
	IMaterial *FindMaterial(char const *pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = 0);
	IMaterial *CreateMaterial(char const *pMaterialName, KeyValues *kv);
	IMaterial *GetMaterial(MaterialHandle_t h);
	MaterialHandle_t FirstMaterial();
	MaterialHandle_t InvalidMaterial();
	MaterialHandle_t NextMaterial(MaterialHandle_t h);
};