#pragma once
#include "../../Modules/Menu/Menu.h"

namespace PaintTraverse
{
	const int Index = 41;
	void __fastcall Hook(void *panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force);
}