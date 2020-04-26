#include "CEngineClient.h"

void CEngineClient::GetScreenSize(int &width_out, int &height_out)
{
	typedef void(__thiscall *FN)(PVOID, int &, int &);
	return GetVFunc<FN>(this, 5)(this, width_out, height_out);
}

void CEngineClient::ServerCmd(const char *szCmdString, bool bReliable)
{
	typedef void(__thiscall *FN)(PVOID, const char *, bool);
	return GetVFunc<FN>(this, 6)(this, szCmdString, bReliable);
}

bool CEngineClient::GetPlayerInfo(int nEntityIndex, PlayerInfo_t *pPlayerInfo)
{
	typedef bool(__thiscall *FN)(PVOID, int, PlayerInfo_t *);
	return GetVFunc<FN>(this, 8)(this, nEntityIndex, pPlayerInfo);
}

bool CEngineClient::Con_IsVisible(void)
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 11)(this);
}

int CEngineClient::GetLocalPlayer(void)
{
	typedef int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 12)(this);
}

float CEngineClient::Time(void)
{
	typedef float(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 14)(this);
}

void CEngineClient::GetViewAngles(Vec3 &va)
{
	typedef void(__thiscall *FN)(PVOID, Vec3 &va);
	return GetVFunc<FN>(this, 19)(this, va);
}

void CEngineClient::SetViewAngles(Vec3 &va)
{
	typedef void(__thiscall *FN)(PVOID, Vec3 &va);
	return GetVFunc<FN>(this, 20)(this, va);
}

int CEngineClient::GetMaxClients(void)
{
	typedef int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 21)(this);
}

bool CEngineClient::IsInGame(void)
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 26)(this);
}

bool CEngineClient::IsConnected(void)
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 27)(this);
}

bool CEngineClient::IsDrawingLoadingImage(void)
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 28)(this);
}

const matrix3x4 &CEngineClient::WorldToScreenMatrix(void)
{
	typedef const matrix3x4 &(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 36)(this);
}

bool CEngineClient::IsTakingScreenshot(void)
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 85)(this);
}

bool CEngineClient::IsHLTV()
{
	typedef bool(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 86)(this);
}

DWORD *CEngineClient::GetNetChannelInfo(void)
{
	typedef DWORD *(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 72)(this);
}

void CEngineClient::ClientCmd_Unrestricted(const char *szCommandString)
{
	typedef void(__thiscall *FN)(PVOID, const char *);
	return GetVFunc<FN>(this, 106)(this, szCommandString);
}