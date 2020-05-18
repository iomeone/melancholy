#include "Misc.h"

void CMisc::Bhop(CBaseEntity *pLocal, CUserCmd *cmd)
{
	if (!pLocal->IsAlive() || pLocal->IsSwimming())
		return;

	static bool JumpState = false;

	if (cmd->buttons & IN_JUMP) {
		if (!JumpState && !pLocal->IsOnGround())
			cmd->buttons &= ~IN_JUMP;

		else if (JumpState)
			JumpState = false;
	}

	else if (!JumpState)
		JumpState = true;
}

void CMisc::Run(CBaseEntity *pLocal, CUserCmd *cmd)
{
	if (Bunnyhop)
		Bhop(pLocal, cmd);

	static ConVar *host_timescale = gInts.ConVars->FindVar("host_timescale");
	host_timescale->SetValue(timescale);
}

CMisc gMisc;