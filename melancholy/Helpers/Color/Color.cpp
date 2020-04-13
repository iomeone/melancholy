#include "Color.h"

RGBA_t::RGBA_t() { }

RGBA_t::RGBA_t(byte _r, byte _g, byte _b, byte _a) {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

byte RGBA_t::R() { return r; }
byte RGBA_t::G() { return g; }
byte RGBA_t::B() { return b; }
byte RGBA_t::A() { return a; }

float RGBA_t::R_flt() { return (static_cast<float>(r) / 255.0f); }
float RGBA_t::G_flt() { return (static_cast<float>(g) / 255.0f); }
float RGBA_t::B_flt() { return (static_cast<float>(b) / 255.0f); }
float RGBA_t::A_flt() { return (static_cast<float>(a) / 255.0f); }

DWORD RGBA_t::DW() { return (static_cast<DWORD>(((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF))); }
Vec3 RGBA_t::V3() { return Vec3(R_flt(), G_flt(), B_flt()); }