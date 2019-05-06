#pragma once
#include <functional>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <vector>
#include "Singleton.h"
#include <map>
#include "Inputs.h"

namespace e
{
	enum class Trigger
	{
		onDown,
		isDown,
		onFree,
		isFree
	};
	class ButtonAction
	{
	public:
		std::function<void()> action;
		InputButton* pButton;
		Trigger trigger;
		ButtonAction(InputButton*, Trigger, std::function<void()>) {}
	};
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void HandleInput();
		void AddButtonAction(Keyboard::Button input, Trigger trigger, const std::function<void()> action);
		void AddButtonAction(Controller::Button input, Trigger trigger, const std::function<void()> action, const int controllerIndex = 0);
		void AddJoystickAction(Controller::Joystick input, const std::function<void(SHORT horizontal, SHORT vertical)> action, const int controllerIndex = 0);
		void SetControllerAmount(char c);
	private:
		void GetInputs();
		SDL_Event e;

		char m_ControllerAmount;
		Keyboard m_Keyboard;
		std::vector<Controller> m_Controllers; //FOR EACH CONTROLLER
		std::vector<ButtonAction> m_ButtonActions;
	};
}