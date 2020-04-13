#pragma once
#include "../../Modules/Menu/Menu.h"

namespace DirectX
{
	const int EndSceneIndex = 42;
	const int ResetIndex = 16;

	HRESULT WINAPI EndSceneHook(IDirect3DDevice9 *pDevice);
	HRESULT WINAPI ResetHook(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParams);
}