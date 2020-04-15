#include "WndProc.h"

long __stdcall WndProc::Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	ImGuiIO &io = ImGui::GetIO();
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	if (gMenu.bOpen && io.WantCaptureMouse &&
			(uMsg == WM_LBUTTONDOWN 
			|| uMsg == WM_LBUTTONUP 
			|| uMsg == WM_RBUTTONDOWN 
			|| uMsg == WM_RBUTTONUP 
			|| uMsg == WM_MBUTTONDOWN 
			|| uMsg == WM_MBUTTONUP 
			|| uMsg == WM_MOUSEWHEEL 
			|| uMsg == WM_MOUSEMOVE)) {
			return TRUE;
		}

	return CallWindowProc(pWindowProc, hWnd, uMsg, wParam, lParam);
}

WNDPROC WndProc::pWindowProc;