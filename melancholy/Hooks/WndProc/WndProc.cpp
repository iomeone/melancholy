#include "WndProc.h"

long __stdcall WndProc::Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return ((gMenu.bOpen && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) ? 1 : CallWindowProcA(pWindowProc, hWnd, uMsg, wParam, lParam));
}

WNDPROC WndProc::pWindowProc;