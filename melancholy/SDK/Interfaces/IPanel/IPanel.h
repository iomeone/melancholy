#pragma once
#include "../../Defines.h"

class IPanel
{
public:
	const char *GetName(unsigned int vgui_panel);
	void SetMouseInputEnabled(unsigned int panel, bool state);
	void SetTopmostPopup(unsigned int panel, bool state);
};