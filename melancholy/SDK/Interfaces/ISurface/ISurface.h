#pragma once
#include "../../Defines.h"

#undef CreateFont

class ISurface
{
public:
	void SetDrawColor(int r, int g, int b, int a);
	void DrawFilledRect(int x0, int y0, int x1, int y1);
	void DrawOutlinedRect(int x0, int y0, int x1, int y1);
	void SetTextFont(unsigned long font);
	void SetTextColor(int r, int g, int b, int a);
	void SetTextPos(int x, int y);
	void PrintText(const wchar_t *text, int text_len);
	void DrawLine(int x, int y, int x1, int y1);
	unsigned long CreateFont();
	void SetFontGlyphSet(unsigned long &font, const char *windows_font_name, int tall, int weight, int blur, int scanlines, int flags);
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall);
	void GetCursorPos(int &x_out, int &y_out);
	void SetCursorAlwaysVisible(bool b);
	void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool horizontal);
	void UnlockCursor();
	void LockCursor();
};