#include "MiniginPCH.h"
#include "Controller.h"

namespace e
{
	using namespace std;

	Controller::Controller(const char index) :
		InputDevice(),
		m_Index{ index },
		m_StateBufferIndex{},
		m_StateBuffers{}
	{}

	void Controller::HandleEvents()
	{
		if (m_IsActive)
		{
			//Update buffer
			m_StateBufferIndex = !m_StateBufferIndex;
			XINPUT_STATE& currentBuffer{ m_StateBuffers[m_StateBufferIndex] };
			ZeroMemory(&currentBuffer, sizeof(XINPUT_STATE));
			if (!XInputGetState(m_Index, &currentBuffer) == ERROR_SUCCESS)
			{
				m_IsActive = false;
				return;
			}
			if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < currentBuffer.Gamepad.sThumbLX && currentBuffer.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
			 && -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < currentBuffer.Gamepad.sThumbLY && currentBuffer.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				currentBuffer.Gamepad.sThumbLX = 0;
				currentBuffer.Gamepad.sThumbLY = 0;
			}
			if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < currentBuffer.Gamepad.sThumbRX && currentBuffer.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
			 && -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < currentBuffer.Gamepad.sThumbRY && currentBuffer.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				currentBuffer.Gamepad.sThumbRX = 0;
				currentBuffer.Gamepad.sThumbRY = 0;
			}
			//Check for events
			const WORD& previousStates{ WORD(m_StateBuffers[!m_StateBufferIndex].Gamepad.wButtons) };
			const WORD& currentStates{ WORD(currentBuffer.Gamepad.wButtons) };
			const WORD  changedStates{ WORD(previousStates ^ currentStates) };
			for (std::pair<const InputIndex, Command*> commandByButton : m_pCommandsByInputIndexOnDown)
			{
				if (currentStates & changedStates & commandByButton.first)
				{
					commandByButton.second->Execute();
				}
			}
			for (std::pair<const InputIndex, Command*> commandByButton : m_pCommandsByInputIndexOnUp)
			{
				if (previousStates & changedStates & commandByButton.first)
				{
					commandByButton.second->Execute();
				}
			}
		}
	}
	bool Controller::Get0DState(const InputIndex& button) const
	{
		if (!m_IsActive) throw runtime_error("Controller inactive!");
		return m_StateBuffers[m_StateBufferIndex].Gamepad.wButtons & button;
	}
	SVector Controller::Get2DState(const InputIndex& joystick) const
	{
		if (!m_IsActive) throw runtime_error("Controller inactive!");
		const XINPUT_GAMEPAD& gamepad{ m_StateBuffers[m_StateBufferIndex].Gamepad };
		switch (Joystick(joystick))
		{
		case Joystick::L:
			return { gamepad.sThumbLX, gamepad.sThumbLY };
		case Joystick::R:
			return { gamepad.sThumbRX, gamepad.sThumbRY };
		};
		return {};
	}
}