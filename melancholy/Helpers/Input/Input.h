#pragma once
#include <Windows.h>
#include <cstdint>
#include <chrono>

struct Input_t
{
	enum KeyState_t {
		none,
		pressed,
		held
	};

	KeyState_t _GetKeyState(int16_t key);
	bool IsPressed(int16_t key);
	bool IsHeld(int16_t key);
	bool IsPressedAndHeld(int16_t key);
};

extern Input_t gInput;