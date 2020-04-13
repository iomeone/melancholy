#include "ISurface.h"

void ISurface::SetDrawColor(int r, int g, int b, int a)
{
	typedef void(__thiscall *FN)(PVOID, int, int, int, int);
	GetVFunc<FN>(this, 11)(this, r, g, b, a);
}

void ISurface::DrawFilledRect(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall *FN)(PVOID, int, int, int, int);
	GetVFunc<FN>(this, 12)(this, x0, y0, x1, y1);
}

void ISurface::DrawOutlinedRect(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall *FN)(PVOID, int, int, int, int);
	GetVFunc<FN>(this, 14)(this, x0, y0, x1, y1);
}

void ISurface::SetTextFont(unsigned long font)
{
	typedef void(__thiscall *FN)(PVOID, unsigned long);
	GetVFunc<FN>(this, 17)(this, font);
}

void ISurface::SetTextColor(int r, int g, int b, int a)
{
	typedef void(__thiscall *FN)(PVOID, int, int, int, int);
	GetVFunc<FN>(this, 19)(this, r, g, b, a);
}

void ISurface::SetTextPos(int x, int y)
{
	typedef void(__thiscall *FN)(PVOID, int, int);
	GetVFunc<FN>(this, 20)(this, x, y);
}

void ISurface::PrintText(const wchar_t *text, int text_len)
{
	typedef void(__thiscall *FN)(PVOID, const wchar_t *, int, int);
	return GetVFunc<FN>(this, 22)(this, text, text_len, 0);
}

void ISurface::DrawLine(int x, int y, int x1, int y1)
{
	typedef void(__thiscall *FN)(PVOID, int, int, int, int);
	return GetVFunc<FN>(this, 15)(this, x, y, x1, y1);
}

unsigned long ISurface::CreateFont()
{
	typedef unsigned int(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 66)(this);
}

void ISurface::SetFontGlyphSet(unsigned long &font, const char *windows_font_name, int tall, int weight, int blur, int scanlines, int flags)
{
	typedef void(__thiscall *FN)(PVOID, unsigned long, const char *, int, int, int, int, int, int, int);
	GetVFunc<FN>(this, 67)(this, font, windows_font_name, tall, weight, blur, scanlines, flags, 0, 0);
}

void ISurface::GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
{
	typedef void(__thiscall *FN)(PVOID, unsigned long, const wchar_t *, int &, int &);
	GetVFunc<FN>(this, 75)(this, font, text, wide, tall);
}

void ISurface::GetCursorPos(int &x_out, int &y_out)
{
	typedef void(__thiscall *FN)(PVOID, int &, int &);
	GetVFunc<FN>(this, 96)(this, x_out, y_out);
}

void ISurface::SetCursorAlwaysVisible(bool b)
{
	typedef void(__thiscall *FN)(PVOID, bool);
	GetVFunc<FN>(this, 52)(this, b);
}

void ISurface::DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool horizontal)
{
	typedef void(__thiscall *FN)(PVOID, int, int, int, int, unsigned int, unsigned int, bool);
	GetVFunc<FN>(this, 118)(this, x0, y0, x1, y1, alpha0, alpha1, horizontal);
}

void ISurface::UnlockCursor()
{
	typedef void(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 61)(this);
}

void ISurface::LockCursor()
{
	typedef void(__thiscall *FN)(PVOID);
	return GetVFunc<FN>(this, 62)(this);
}