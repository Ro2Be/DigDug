#pragma once
#include "Singleton.h"
#include "Keyboard.h"
#include "Controller.h"

namespace e
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		void HandleInputEvents();
		void RefreshActiveInputDevices();
		Keyboard& GetKeyboard();
		Controller& GetController(char c);
	private:
		Keyboard m_Keyboard;
		Controller m_Controllers[4];
	};
}