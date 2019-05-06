#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <string>
#include <Windows.h>
#include "Minigin.h"
namespace e
{
	using namespace std;
	void InputManager::HandleInput()
	{
		GetInputs();
		for (ButtonAction buttonAction : m_ButtonActions)
		{
			switch (buttonAction.trigger)
			{
			case Trigger::onDown:
				if (!buttonAction.pButton->GetState(1) && buttonAction.pButton->GetState(0)) buttonAction.action();
				break;
			case Trigger::isDown:
				if (buttonAction.pButton->GetState(0)) buttonAction.action();
				break;
			case Trigger::onFree:
				if (buttonAction.pButton->GetState(1) && !buttonAction.pButton->GetState(0)) buttonAction.action();
				break;
			case Trigger::isFree:
				if (!buttonAction.pButton->GetState(0)) buttonAction.action();
				break;
			}
		}
	}
	void InputManager::AddButtonAction(Keyboard::Button input, Trigger trigger, const std::function<void()> action)
	{
		m_ButtonActions.push_back(ButtonAction(&m_Keyboard.buttons[input], trigger, action));

	}
	void InputManager::AddButtonAction(Controller::Button input, Trigger trigger, const std::function<void()> action, const int controllerIndex)
	{
		m_ButtonActions.push_back(ButtonAction(&m_Controllers[controllerIndex].buttons[input], trigger, action));
	}
	void InputManager::AddJoystickAction(Controller::Joystick input, const std::function<void(SHORT horizontal, SHORT vertical)> action, const int controllerIndex)
	{
		UNREFERENCED_PARAMETER(input);
		UNREFERENCED_PARAMETER(action);
		UNREFERENCED_PARAMETER(controllerIndex);
		//TODO
	}
	void InputManager::SetControllerAmount(char c)
	{
		if (c <= XUSER_MAX_COUNT) m_ControllerAmount = c;
		else throw std::invalid_argument("Engine does not support that amount of controllers");
	}
	void InputManager::GetInputs()
	{
		SDL_Event sdlEvent;
		SDL_PollEvent(&sdlEvent);
		if (sdlEvent.type == SDL_QUIT) Minigin::quit = true;
		//KEYBOARD
		for (std::pair<Keyboard::Button, InputButton> buttonInput : m_Keyboard.buttons)
		{
			buttonInput.second.AddState(GetAsyncKeyState(int(buttonInput.first)) & 0x8000);
		}
		//CONTROLLERS
		for (int i{}; i < m_ControllerAmount; ++i)
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));
			if (XInputGetState(i, &state) == ERROR_SUCCESS)
			{
				for (std::pair<Controller::Button, InputButton> buttonInput : m_Controllers[i].buttons)
				{
					buttonInput.second.AddState(state.Gamepad.wButtons & WORD(buttonInput.first));
				}
				if (m_Controllers[i].rightJoystick != nullptr)
				{
					if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbLX && state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
					 && -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbLY && state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
					{
						state.Gamepad.sThumbLX = 0;
						state.Gamepad.sThumbLY = 0;
					}
					m_Controllers[i].rightJoystick->SetState(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
				}
				if (m_Controllers[i].rightJoystick != nullptr)
				{
					if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbRX && state.Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
					 && -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < state.Gamepad.sThumbRY && state.Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
					{
						state.Gamepad.sThumbRX = 0;
						state.Gamepad.sThumbRY = 0;
					}
					m_Controllers[i].rightJoystick->SetState(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
				}
			}
		}
	}
}