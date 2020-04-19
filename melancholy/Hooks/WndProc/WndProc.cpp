#include "WndProc.h"

long __stdcall WndProc::Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (gMenu.bOpen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return 1;

	return CallWindowProc(pWindowProc, hWnd, uMsg, wParam, lParam);
}

WNDPROC WndProc::pWindowProc;