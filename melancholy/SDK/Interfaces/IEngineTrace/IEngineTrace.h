#pragma once
#include "../../Defines.h"

class IEngineTrace
{
public:
	void TraceRay(const Ray_t &ray, unsigned int nMask, ITraceFilter *pTraceFilter, CGameTrace *pTrace);
};