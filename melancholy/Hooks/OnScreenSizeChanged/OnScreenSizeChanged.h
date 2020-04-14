#pragma once

namespace OnScreenSizeChanged {
	const int Index = 111;
	void __fastcall Hook(void *surface, int edx, int nOldWidth, int nOldHeight);
}