#include "DirectX.h"

using EndSceneFN = HRESULT(WINAPI *)(IDirect3DDevice9 *);
using ResetFN = HRESULT(WINAPI *)(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *);

HRESULT WINAPI DirectX::EndSceneHook(IDirect3DDevice9 *pDevice)
{
	/*pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);*///uncomment if you're going to use DX for drawing (fixes drawing colors)

	VMTManager &hook = VMTManager::GetHook(pDevice);
	
	gMenu.Run(pDevice);

	return hook.GetMethod<EndSceneFN>(EndSceneIndex)(pDevice);
}

HRESULT WINAPI DirectX::ResetHook(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParams)
{
	VMTManager &hook = VMTManager::GetHook(pDevice);
	
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
	
	return hook.GetMethod<ResetFN>(ResetIndex)(pDevice, pPresentParams);
}