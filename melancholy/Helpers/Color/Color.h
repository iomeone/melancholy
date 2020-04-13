#pragma once
#include "../Math/Math.h"

typedef unsigned char byte;
typedef unsigned long DWORD;

struct RGBA_t
{
	byte r = 0;
	byte g = 0;
	byte b = 0;
	byte a = 0;

	RGBA_t();
	RGBA_t(byte _r, byte _g, byte _b, byte _a);

	byte R(), G(), B(), A();
	float R_flt(), G_flt(), B_flt(), A_flt();
	DWORD DW();
	Vec3 V3();
};