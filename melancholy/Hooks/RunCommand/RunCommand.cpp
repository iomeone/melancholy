#include "RunCommand.h"

using fn = void(__thiscall *)(void *, CBaseEntity *, CUserCmd *, IMoveHelper *);

void __fastcall RunCommand::Hook(IPrediction *prediction, int edx, CBaseEntity *entity, CUserCmd *cmd, IMoveHelper *move_helper)
{
	VMTManager &hk = VMTManager::GetHook(prediction);
	hk.GetMethod<fn>(Index)(prediction, entity, cmd, move_helper);

	if (move_helper && !gInts.MoveHelper)
		gInts.MoveHelper = move_helper;
}