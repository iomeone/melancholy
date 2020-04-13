#include "CEntityList.h"

CBaseEntity *CEntityList::GetClientEntity(int nEntityIndex)
{
	typedef CBaseEntity *(__thiscall *FN)(PVOID, int);
	return GetVFunc<FN>(this, 3)(this, nEntityIndex);
}

CBaseEntity *CEntityList::GetClientEntityFromHandle(int hEntity)
{
	typedef CBaseEntity *(__thiscall *FN)(PVOID, int);
	return GetVFunc<FN>(this, 4)(this, hEntity);
}

int CEntityList::GetHighestEntityIndex(void)
{
	typedef int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 6)(this);
}