#pragma once
#include <Windows.h>

class CPattern
{
public:
	DWORD FindPattern(DWORD dwAddress, DWORD dwLength, PCCH szPattern);
	HMODULE GetModuleHandleSafe(PCCH szModuleName);
	DWORD FindInClient(PCCH szPattern);
	DWORD FindInEngine(PCCH szPattern);
	DWORD FindInModule(PCCH szModuleName, PCCH szPattern);
};

extern CPattern gPattern;