#include "Hooks.h"

void Hooks_t::Initialize()
{
	if (gInts.ClientMode) {
		ClientModeHook = new VMTBaseManager();
		ClientModeHook->Init(gInts.ClientMode);
		ClientModeHook->HookMethod(&CreateMove::Hook, CreateMove::Index);
		ClientModeHook->HookMethod(&OverrideView::Hook, OverrideView::Index);
		ClientModeHook->HookMethod(&ShouldDrawViewmodel::Hook, ShouldDrawViewmodel::Index);
		ClientModeHook->Rehook();
	}

	if (gInts.DXDevice) {
		DirectXHook = new VMTBaseManager();
		DirectXHook->Init(reinterpret_cast<DWORD **>(gInts.DXDevice));
		DirectXHook->HookMethod(&DirectX::EndSceneHook, DirectX::EndSceneIndex);
		DirectXHook->HookMethod(&DirectX::ResetHook, DirectX::ResetIndex);
		DirectXHook->Rehook();
	}

	if (gInts.Panels) {
		PanelsHook = new VMTBaseManager();
		PanelsHook->Init(gInts.Panels);
		PanelsHook->HookMethod(&PaintTraverse::Hook, PaintTraverse::Index);
		PanelsHook->Rehook();
	}

	if (gInts.Surface) {
		SurfaceHook = new VMTBaseManager();
		SurfaceHook->Init(gInts.Surface);
		SurfaceHook->HookMethod(&LockCursor::Hook, LockCursor::Index);
		SurfaceHook->HookMethod(&OnScreenSizeChanged::Hook, OnScreenSizeChanged::Index);
		SurfaceHook->Rehook();
	}

	if (gInts.ModelRender) {
		/*ModelRenderHook = new VMTBaseManager();
		ModelRenderHook->Init(gInts.ModelRender);
		ModelRenderHook->HookMethod(&DrawModelExecute::Hook, DrawModelExecute::Index);
		ModelRenderHook->Rehook();*/
	}

	if (gInts.RenderView) {
		RenderViewHook = new VMTBaseManager();
		RenderViewHook->Init(gInts.RenderView);
		RenderViewHook->HookMethod(&SceneEnd::Hook, SceneEnd::Index);
		RenderViewHook->Rehook();
	}

	if (gInts.Prediction) {
		PredictionHook = new VMTBaseManager();
		PredictionHook->Init(gInts.Prediction);
		PredictionHook->HookMethod(&RunCommand::Hook, RunCommand::Index);
		PredictionHook->Rehook();
	}

	if (gInts.Client) {
		ClientHook = new VMTBaseManager();
		ClientHook->Init(gInts.Client);
		ClientHook->HookMethod(&FrameStageNotify::Hook, FrameStageNotify::Index);
		ClientHook->Rehook();
	}

	HWND hwTF2Window = 0;

	while (!hwTF2Window)
		hwTF2Window = FindWindowA(0, "Team Fortress 2");

	WndProc::pWindowProc = (WNDPROC)SetWindowLongPtr(hwTF2Window, GWL_WNDPROC, (LONG_PTR)&WndProc::Hook);
}

Hooks_t gHooks;