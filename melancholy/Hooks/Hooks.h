#pragma once
#include "CreateMove/CreateMove.h"
#include "DirectX/DirectX.h"
#include "PaintTraverse/PaintTraverse.h"
#include "LockCursor/LockCursor.h"
#include "WndProc/WndProc.h"
#include "OverrideView/OverrideView.h"
#include "ShouldDrawViewmodel/ShouldDrawViewmodel.h"
#include "DrawModelExecute/DrawModelExecute.h"
#include "SceneEnd/SceneEnd.h"
#include "RunCommand/RunCommand.h"
#include "FrameStageNotify/FrameStageNotify.h"
#include "OnScreenSizeChanged/OnScreenSizeChanged.h"
#include "LevelInit/LevelInit.h"

struct Hooks_t
{
	VMTBaseManager *ClientModeHook		= nullptr;
	VMTBaseManager *DirectXHook			= nullptr;
	VMTBaseManager *PanelsHook			= nullptr;
	VMTBaseManager *SurfaceHook			= nullptr;
	VMTBaseManager *ModelRenderHook		= nullptr;
	VMTBaseManager *RenderViewHook		= nullptr;
	VMTBaseManager *PredictionHook		= nullptr;
	VMTBaseManager *ClientHook			= nullptr;

	void Initialize();
};

extern Hooks_t gHooks;