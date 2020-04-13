#pragma once
#include "../../Modules/ESP/ESP.h"

namespace DrawModelExecute
{
	const int Index = 19;

	enum struct ChamMode_t {
		DEFAULT = -1,
		VISIBLE,
		INVISIBLE,
		ALWAYS
	};

	void __stdcall Hook(const DrawModelState_t &state, const ModelRenderInfo_t &info, matrix3x4 *matrix);
}