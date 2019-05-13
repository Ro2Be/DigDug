#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <string>
#include <Windows.h>

namespace e
{
	using namespace std;
	InputManager::InputManager() :
		m_Keyboard{},
		m_Controllers{ { 0 }, { 1 }, { 2 }, { 3 } }
	{
	}
	void InputManager::HandleInputEvents()
	{
		m_Keyboard.HandleEvents();
		for (Controller& c : m_Controllers) c.HandleEvents();
	}
	void InputManager::RefreshActiveInputDevices()
	{
		for (Controller& c : m_Controllers) c.SetIsActive(false);
	}
	Keyboard& InputManager::GetKeyboard()
	{
		return m_Keyboard;
	}
	Controller& InputManager::GetController(char index)
	{
		return m_Controllers[index];
	}
}