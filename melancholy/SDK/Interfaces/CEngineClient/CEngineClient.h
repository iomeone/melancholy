#pragma once
#include "../../Defines.h"

class CEngineClient
{
public:
	void GetScreenSize(int &width_out, int &height_out);
	void ServerCmd(const char *szCmdString, bool bReliable = true);
	bool GetPlayerInfo(int nEntityIndex, PlayerInfo_t *pPlayerInfo);
	bool Con_IsVisible(void);
	int GetLocalPlayer(void);
	float Time(void);
	void GetViewAngles(Vec3 &va);
	void SetViewAngles(Vec3 &va);
	int GetMaxClients(void);
	bool IsInGame(void);
	bool IsConnected(void);
	bool IsDrawingLoadingImage(void);
	const matrix3x4 &WorldToScreenMatrix(void);
	bool IsTakingScreenshot(void);
	bool IsHLTV();
	DWORD *GetNetChannelInfo(void);
	void ClientCmd_Unrestricted(const char *szCommandString);
};