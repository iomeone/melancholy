#include "CreateMove.h"

using fn = bool(__thiscall *)(void *, float, CUserCmd *);

bool __fastcall CreateMove::Hook(void *client_mode, int edx, float input_sample_frametime, CUserCmd *cmd)
{
	VMTManager &hk = VMTManager::GetHook(client_mode);
	bool original = hk.GetMethod<fn>(Index)(client_mode, input_sample_frametime, cmd);

	if (!cmd || !cmd->command_number)
		return false;

	CBaseEntity *pLocal = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

	if (pLocal)
	{
		gLocalInfo.CurrentTargetIndex = -1; //better to do this here
		gLocalInfo.PredStart = gLocalInfo.PredEnd = Vec3();

		CBaseCombatWeapon *pLocalWeapon = pLocal->GetActiveWeapon();

		if (pLocalWeapon)
		{
			gMisc.Run(pLocal, cmd);
			gLocalInfo.CanHeadShot = pLocalWeapon->CanWeaponHeadShot();
			Utils::LocalPrediction(pLocal, cmd);
			gAimbot.Run(pLocal, pLocalWeapon, cmd);
		}
	}

	//lbutton smooth shoot thingy thing
	if (gAimbot.AimKey == 1) {
		if ((cmd->buttons & IN_ATTACK) && (gAimbot.AimTime > 0.0f && !gAimbot.AimFinished))
			cmd->buttons &= ~IN_ATTACK; //not perfect but it works
	}

	return (gAimbot.Silent ? false : original);
}