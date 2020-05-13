#pragma once
#include "../../Modules/Chams/Chams.h"

namespace DrawModelExecute {
	const int Index = 19;
	void __stdcall Hook(const DrawModelState_t &state, const ModelRenderInfo_t &info, matrix3x4 *matrix);
}