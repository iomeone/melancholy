#pragma once
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_impl_win32.h"
#include "../../ImGui/imgui_impl_dx9.h"
#include "../ESP/ESP.h"
#include "../Chams/Chams.h"
#include "../Misc/Misc.h"
#include "../Glow/Glow.h"

class CMenu
{
private:
	const int windowX = 400;
	const int windowY = 200;
	const int windowW = 600;
	const int windowH = 500;
	const char *windowTitle = "melancholy";
	const ImGuiWindowFlags windowFlags = (ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoSavedSettings);

	struct Spectator_t {
		std::string name = "";
		std::string mode = "";
	};

	std::vector<Spectator_t> Spectators;

public:
	bool bOpen = false;

	void Run(IDirect3DDevice9 *pDevice);
};

extern CMenu gMenu;