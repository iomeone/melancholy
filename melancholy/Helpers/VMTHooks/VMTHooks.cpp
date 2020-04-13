#include "VMTHooks.h"

VMTBaseManager& VMTBaseManager::Init(void* inst, unsigned int offset, unsigned int vfuncs)
{
	_vftable = &_getvtbl(inst, offset);
	_oldvmt = *_vftable;

	if (!vfuncs) {
		vfuncs = CountFuncs(_oldvmt);
	}

	void** arr = _array = (void**) ::malloc((vfuncs + 4) * sizeof(void*));
	arr[0] = this;
	arr[1] = (void*)GUARD;
	(arr + 3)[vfuncs] = nullptr;

	{
		unsigned int i = -1;
		do arr[i + 3] = _oldvmt[i];
		while (++i < vfuncs);
	}

	return *this;
}

void VMTBaseManager::Kill()
{
	if (IsInitialized()) {
		Unhook();
		_vftable = nullptr;
	}

	::free(_array);
	_array = nullptr;
}

bool VMTBaseManager::IsInitialized() const
{
	return _vftable != nullptr;
}

VMTBaseManager& VMTBaseManager::HookMethod(void* newfunc, unsigned int index)
{
	_array[index + 3] = newfunc;
	return *this;
}

VMTBaseManager& VMTBaseManager::UnhookMethod(unsigned int index)
{
	_array[index + 3] = _oldvmt[index];
	return *this;
}

void VMTBaseManager::EraseHooks()
{
	unsigned int i = 0;
	void** vmt = _array + 3;
	do vmt[i] = _oldvmt[i];
	while (vmt[++i]);
}

VMTBaseManager& VMTBaseManager::Unhook()
{
	*_vftable = _oldvmt;
	return *this;
}

VMTBaseManager& VMTBaseManager::Rehook()
{
	*_vftable = _array + 3;
	return *this;
}

bool VMTBaseManager::Hooked() const
{
	return *_vftable != _oldvmt;
}

bool VMTBaseManager::HookPresent(void* inst, unsigned int offset)
{
	void** vmt = _getvtbl(inst, offset);
	return vmt[-2] == (void*)GUARD;
}

VMTBaseManager& VMTBaseManager::GetHook(void* inst, unsigned int offset)
{
	void** vmt = _getvtbl(inst, offset);
	return *reinterpret_cast<VMTBaseManager*>(vmt[-3]);
}

void**& VMTBaseManager::_getvtbl(void* inst, unsigned int offset)
{
	return *reinterpret_cast<void***>((char*)inst + offset);
}

VMTManager::VMTManager(void* inst, unsigned int offset, unsigned int vfuncs)
{
	Init(inst, offset, vfuncs).Rehook();
}

VMTManager::~VMTManager()
{
	Kill();
}

void VMTManager::Poof()
{
	_vftable = nullptr;
}

VMTManager& VMTManager::GetHook(void* inst, unsigned int offset)
{
	return static_cast<VMTManager&>(VMTBaseManager::GetHook(inst, offset));
}