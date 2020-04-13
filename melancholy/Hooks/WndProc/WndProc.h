#pragma once
#include "../../Modules/Menu/Menu.h"

extern long ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef long(__stdcall *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

namespace WndProc
{
	long __stdcall Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	extern WNDPROC pWindowProc;
}