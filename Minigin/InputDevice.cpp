#include "MiniginPCH.h"
#include "InputDevice.h"
namespace e
{
	using namespace std;
	InputDevice::InputDevice() :
		m_IsActive{ true },
		m_pCommandsByInputIndexOnDown{}
	{
	}
	InputDevice::~InputDevice()
	{
		for (pair<InputIndex, Command*> pCommandByInputIndex : m_pCommandsByInputIndexOnDown) delete pCommandByInputIndex.second;
		for (pair<InputIndex, Command*> pCommandByInputIndex : m_pCommandsByInputIndexOnUp) delete pCommandByInputIndex.second;
	}
	void InputDevice::AddCommand(const InputIndex& input0DIndex, bool event, Command* pCommand)
	{
		if(event) m_pCommandsByInputIndexOnDown[input0DIndex] = pCommand;
		else	  m_pCommandsByInputIndexOnUp  [input0DIndex] = pCommand;
		
	}
	void InputDevice::RemoveCommands(const InputIndex& inputIndex)
	{
		m_pCommandsByInputIndexOnDown.erase(inputIndex);
		m_pCommandsByInputIndexOnUp.erase(inputIndex);
	}
	bool InputDevice::GetIsActive() const
	{
		return m_IsActive;
	}
	void InputDevice::SetIsActive(bool isActive)
	{
		m_IsActive = isActive;
	}
}