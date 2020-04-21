#include "IEngineVGui.h"

bool IEngineVGui::IsGameUIVisible() {
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 2)(this);
}