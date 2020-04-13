#include "IMoveHelper.h"

void IMoveHelper::SetHost(CBaseEntity *pHost)
{
	typedef void(__thiscall *FN)(PVOID, CBaseEntity *);
	GetVFunc<FN>(this, 0)(this, pHost);
}