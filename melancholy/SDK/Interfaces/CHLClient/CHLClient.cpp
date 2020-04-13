#include "CHLClient.h"

CClientClass *CHLClient::GetAllClasses(void)
{
	typedef CClientClass *(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 8)(this);
}

bool CHLClient::ShouldDrawEntity(CBaseEntity *pEntity)
{
	typedef bool(__thiscall *FN)(PVOID, CBaseEntity *);
	return GetVFunc<FN>(this, 12)(this, pEntity);
}