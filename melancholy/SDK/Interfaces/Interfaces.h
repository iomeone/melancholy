#pragma once
#include "CEngineClient/CEngineClient.h"
#include "CEntityList/CEntityList.h"
#include "CGlobals/CGlobals.h"
#include "CHLClient/CHLClient.h"
#include "CModelInfo/CModelInfo.h"
#include "CClientModeShared/CClientModeShared.h"
#include "IEngineTrace/IEngineTrace.h"
#include "IPrediction/IPrediction.h" //includes IMoveHelper
#include "IGameMovement/IGameMovement.h"
#include "IPanel/IPanel.h"
#include "ISurface/ISurface.h"
#include "IMaterialSystem/IMaterialSystem.h"
#include "CModelRender/CModelRender.h"
#include "CRenderView/CRenderView.h"
#include "IEngineVGui/IEngineVGui.h"

struct Interfaces_t
{
	CEngineClient *Engine			= nullptr;
	CEntityList *EntityList			= nullptr;
	CGlobals *Globals				= nullptr;
	CHLClient *Client				= nullptr;
	CModelInfo *ModelInfo			= nullptr;
	CClientModeShared *ClientMode	= nullptr;
	IEngineTrace *EngineTrace		= nullptr;
	IMoveHelper *MoveHelper			= nullptr; //set in RunCommand hook
	IPrediction *Prediction			= nullptr;
	IGameMovement *GameMovement		= nullptr;
	IPanel *Panels					= nullptr;
	ISurface *Surface				= nullptr;
	IMaterialSystem *MatSystem		= nullptr;
	CModelRender *ModelRender		= nullptr;
	CRenderView *RenderView			= nullptr;
	IEngineVGui *EngineVGui			= nullptr;

	DWORD DXDevice = 0x0;

	void Initialize();
};

extern Interfaces_t gInts;