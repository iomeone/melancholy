#include "Interface.h"

PVOID CInterface::Get(PCCH szModule, PCCH szObject)
{
	DWORD CreateInterface	= (DWORD)GetProcAddress(GetModuleHandleA(szModule), "CreateInterface");
	DWORD ShortJump			= (DWORD)CreateInterface + 5;
	DWORD Jump				= (((DWORD)CreateInterface + 5) + *(DWORD*)ShortJump) + 4;
	Interface_t* List		= **(Interface_t***)(Jump + 6);

	do
	{
		if (List)
			if (strstr(List->szInterfaceName, szObject) && (strlen(List->szInterfaceName) - strlen(szObject)) < 5)
				return List->Interface();

	} while (List = List->NextInterface);

	return nullptr;
}

CInterface gInterface;