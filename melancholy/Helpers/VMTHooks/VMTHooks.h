#pragma once
#include <cstdlib>

//credits to Casual_Hacker

inline unsigned int CountFuncs(void** pVMT)
{
	unsigned int i = -1;
	do ++i; while (pVMT[i]);
	return i;
}

inline int FindFunc(void** pVMT, void* pFunc, unsigned int vfuncs = 0)
{
	if (!vfuncs)
		vfuncs = CountFuncs(pVMT);

	for (unsigned int i = 0; i < vfuncs; i++)
		if (pVMT[i] == pFunc)
			return i;

	return -1;
}

class VMTBaseManager
{
public:
	enum { GUARD = 0xFAC0D775 }; //4206942069 huehuehuehuehue

	VMTBaseManager& Init(void* inst, unsigned int offset = 0, unsigned int vfuncs = 0);
	void Kill();
	bool IsInitialized() const;
	VMTBaseManager& HookMethod(void* newfunc, unsigned int index);
	VMTBaseManager& UnhookMethod(unsigned int index);
	void EraseHooks();
	VMTBaseManager& Unhook();
	VMTBaseManager& Rehook();
	bool Hooked() const;
	template <typename Fn>
	const Fn& GetMethod(unsigned int index) const {		
		return *(const Fn*)&_oldvmt[index];
	}
	static bool HookPresent(void* inst, unsigned int offset = 0);
	static VMTBaseManager& GetHook(void* inst, unsigned int offset = 0);

protected:
	static void**& _getvtbl(void* inst, unsigned int offset);

protected:
	void*** _vftable;
	void** _oldvmt;
	void** _array;
};

class VMTManager : public VMTBaseManager
{
	VMTManager(const VMTManager&);

public:
	VMTManager(void* inst, unsigned int offset = 0, unsigned int vfuncs = 0);
	~VMTManager();

	void Poof();

	static VMTManager& GetHook(void* inst, unsigned int offset = 0);
};