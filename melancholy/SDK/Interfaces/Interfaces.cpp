#include "Interfaces.h"

//TODO: add fail checks

void Interfaces_t::Initialize()
{
	Engine			= reinterpret_cast<CEngineClient *>			(gInterface.Get("engine.dll", "VEngineClient013"));
	EntityList		= reinterpret_cast<CEntityList *>			(gInterface.Get("client.dll", "VClientEntityList003"));
	Globals			= *reinterpret_cast<CGlobals **>			(gPattern.FindInEngine("A1 ? ? ? ? 8B 11 68") + 0x8);
	Client			= reinterpret_cast<CHLClient *>				(gInterface.Get("client.dll", "VClient017"));
	ModelInfo		= reinterpret_cast<CModelInfo *>			(gInterface.Get("engine.dll", "VModelInfoClient006"));
	ClientMode		= **reinterpret_cast<CClientModeShared ***>	(gPattern.FindInClient("8B 0D ? ? ? ? 8B 02 D9 05") + 0x2);
	EngineTrace		= reinterpret_cast<IEngineTrace *>			(gInterface.Get("engine.dll", "EngineTraceClient003"));
	Prediction		= reinterpret_cast<IPrediction *>			(gInterface.Get("client.dll", "VClientPrediction001"));
	GameMovement	= reinterpret_cast<IGameMovement *>			(gInterface.Get("client.dll", "GameMovement001"));
	Panels			= reinterpret_cast<IPanel*>					(gInterface.Get("vgui2.dll", "VGUI_Panel009"));
	Surface			= reinterpret_cast<ISurface*>				(gInterface.Get("vguimatsurface.dll", "VGUI_Surface030"));
	MatSystem		= reinterpret_cast<IMaterialSystem*>		(gInterface.Get("MaterialSystem.dll", "VMaterialSystem081"));
	ModelRender		= reinterpret_cast<CModelRender*>			(gInterface.Get("engine.dll", "VEngineModel016"));
	RenderView		= reinterpret_cast<CRenderView*>			(gInterface.Get("engine.dll", "VEngineRenderView014"));
	EngineVGui		= reinterpret_cast<IEngineVGui*>			(gInterface.Get("engine.dll", "VEngineVGui001"));
	GlowObject		= *reinterpret_cast<CGlowObjectManager **>	(gPattern.FindInClient("8B 0D ? ? ? ? A1 ? ? ? ? 56 8B 37") + 0x2);
	ConVars			= reinterpret_cast<ICvar*>					(gInterface.Get("vstdlib.dll", "VEngineCvar004"));
	DXDevice		= **reinterpret_cast<DWORD **>				(gPattern.FindInModule("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 0x1);
}

Interfaces_t gInts;