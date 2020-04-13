#include "Input.h"

Input_t::KeyState_t Input_t::_GetKeyState(int16_t key)
{
	static KeyState_t keys[256] = { none };

	if (GetKeyState(key) & 0x8000)
	{
		if (keys[key] == pressed)
			keys[key] = held;

		else if (keys[key] != held)
			keys[key] = pressed;
	}

	else keys[key] = none;

	return keys[key];
}

bool Input_t::IsPressed(int16_t key) {
	return (_GetKeyState(key) == pressed);
}

bool Input_t::IsHeld(int16_t key) {
	return (_GetKeyState(key) == held);
}

bool Input_t::IsPressedAndHeld(int16_t key) {
	KeyState_t key_state = _GetKeyState(key);

	static std::chrono::time_point<std::chrono::steady_clock> start[256] = { std::chrono::steady_clock::now() };

	if (key_state == pressed) {
		start[key] = std::chrono::steady_clock::now();
		return true;
	}

	if (key_state == held && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start[key]).count() > 400)
		return true;

	return false;
}

Input_t gInput;