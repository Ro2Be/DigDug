#pragma once
#include "InputDevice.h"
#include <XInput.h>

namespace e
{
	class Controller final : public InputDevice
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
		enum class Joystick : bool
		{
			L,
			R
		};
		Controller(char index);
		virtual void HandleEvents() override;
		virtual bool Get0DState(const InputIndex& button) const override;
		virtual SVector Get2DState(const InputIndex& joystick) const override;
	private:
		char m_Index;
		bool m_StateBufferIndex;
		XINPUT_STATE m_StateBuffers[2];
	};
}