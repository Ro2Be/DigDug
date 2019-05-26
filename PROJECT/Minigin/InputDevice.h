#pragma once
#include <unordered_map>
#include "Command.h"
namespace e
{
	//0D input (bool) { released = false, triggered = true }
	class InputDevice
	{
	public:
		using InputIndex = DWORD;
		//FUNCTIONS
		InputDevice();
		virtual ~InputDevice();
		void AddCommand(const InputIndex& input0DIndex, bool event, Command* pCommand);
		void RemoveCommands(const InputIndex& button);
		bool GetIsActive() const;
		void SetIsActive(bool isActive);
		//VIRTUALS
		virtual void HandleEvents() = 0;
		virtual bool Get0DState(const InputIndex& input0DIndex) const = 0;
		virtual SVector Get2DState(const InputIndex& input2DIndex) const = 0;
	protected:
		bool m_IsActive;
		std::unordered_map<InputIndex, Command*> m_pCommandsByInputIndexOnDown;
		std::unordered_map<InputIndex, Command*> m_pCommandsByInputIndexOnUp;
	};
};