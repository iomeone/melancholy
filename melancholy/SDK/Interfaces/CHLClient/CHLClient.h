#pragma once
#include "../../Defines.h"

class CHLClient
{
public:
	CClientClass *GetAllClasses(void);
	bool ShouldDrawEntity(CBaseEntity *pEntity);
};