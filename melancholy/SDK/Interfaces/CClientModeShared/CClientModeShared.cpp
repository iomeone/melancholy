#include "CClientModeShared.h"

bool CClientModeShared::IsChatPanelOutOfFocus(void)
{
	typedef PVOID(__thiscall *FN)(PVOID);
	PVOID CHudChat = GetVFunc<FN>(this, 19)(this);

	if (CHudChat)
		return *reinterpret_cast<float *>((reinterpret_cast<DWORD>(CHudChat) + 0xFC)) == 0.0f;

	return false;
}