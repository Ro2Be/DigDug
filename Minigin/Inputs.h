#pragma once
#include "Windows.h"
#include "Structs.h"

class InputButton
{
public:
	//GET STATE X FRAMES IN TIME
	bool GetState(const unsigned int i) const
	{
		return state & (1 << i);
	}
	//SAVES CURRENT STATE
	void AddState(const bool isDown)
	{
		state = state << 1;
		if (isDown) state |= 1;
	}
private:
	char state;
};

class InputJoystick
{
public:
	void SetState(signed short int h, signed short int v)
	{
		horizontal = h;
		vertical = v;
	}
private:
	signed short int horizontal;
	signed short int vertical;
};

class Keyboard
{
public:
	enum class Button : int
	{
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z'
	};
	std::map<Button, InputButton> buttons;
};

class Controller
{
public:
	enum class Button : WORD
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		UP = XINPUT_GAMEPAD_DPAD_UP,
		DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		START = XINPUT_GAMEPAD_START,
		BACK = XINPUT_GAMEPAD_BACK,
		L_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
		R_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,
		L_TRIGGER = XINPUT_GAMEPAD_LEFT_SHOULDER,
		R_TRIGGER = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};
	enum class Joystick
	{
		LEFT,
		RIGHT
	};
	std::map<Button, InputButton> buttons;
	InputJoystick* leftJoystick;
	InputJoystick* rightJoystick;
};