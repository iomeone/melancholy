#include "IEngineTrace.h"

void IEngineTrace::TraceRay(const Ray_t &ray, unsigned int nMask, ITraceFilter *pTraceFilter, CGameTrace *pTrace)
{
	typedef void(__thiscall *FN)(PVOID, const Ray_t &, unsigned int, ITraceFilter *, CGameTrace *);
	return GetVFunc<FN>(this, 4)(this, ray, nMask, pTraceFilter, pTrace);
}