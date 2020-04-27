#include "PaintTraverse.h"

using fn = void(__thiscall *)(void *, unsigned int, bool, bool);

void __fastcall PaintTraverse::Hook(void *panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force)
{
	if (gESP.Active && gESP.NoScope) {
		const char *szHudScope = gInts.Panels->GetName(vgui_panel);

		if (szHudScope[0] == 'H' && szHudScope[3] == 'S' && szHudScope[8] == '\0')
			return;
	}

	VMTManager &hk = VMTManager::GetHook(panels);
	hk.GetMethod<fn>(Index)(panels, vgui_panel, force_repaint, allow_force);

	static unsigned int top_panel;

	if (top_panel == 0) {
		const char *name = gInts.Panels->GetName(vgui_panel);

		if (strstr(name, "FocusOverlayPanel"))
			top_panel = vgui_panel;
	}

	if (top_panel == vgui_panel)
	{
		static bool init_screen_size = false;

		if (!init_screen_size) {
			if (!gScreenSize.w || !gScreenSize.h)
				gScreenSize.Update();

			else init_screen_size = true;
		}

		if (!init_screen_size)
			return;

		CBaseEntity *local = gInts.EntityList->GetClientEntity(gInts.Engine->GetLocalPlayer());

		if (local && local->IsAlive())
			local->ForceTauntCam(gESP.Active && gESP.Thirdperson);

		gESP.Run();

		if (!gInts.Engine->IsConnected() && !gInts.Engine->IsDrawingLoadingImage()) 
		{
			gInts.Panels->SetTopmostPopup(vgui_panel, true);

			static std::string msg0 = "melancholy by spook953";
			static std::string msg1 = ("build date " + std::string(__DATE__));

			RGBA_t col = Utils::Rainbow();
			static int w = 0, h = 0;

			gInts.Surface->GetTextSize(gESP.DrawMark.dwFont, Utils::ToWC(msg0.c_str()), w, h);
			gESP.DrawMark.String((gScreenSize.w / 2) - (w / 2), 100, col, msg0.c_str());

			gInts.Surface->GetTextSize(gESP.DrawMark.dwFont, Utils::ToWC(msg1.c_str()), w, h);
			gESP.DrawMark.String((gScreenSize.w / 2) - (w / 2), 115, col, msg1.c_str());
		}
	}
}