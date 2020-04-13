#pragma once
#include "../../Defines.h"

class CEntityList
{
public:
	CBaseEntity *GetClientEntity(int nEntityIndex);
	CBaseEntity *GetClientEntityFromHandle(int hEntity);
	int GetHighestEntityIndex(void);
};