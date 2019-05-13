#pragma once
#include "BodyComponent.h"
namespace e
{
	class MassComponent : public Component
	{
	public:
		MassComponent(short mass);
		virtual void WakeUp(const GameObject* pParent) override;
	private:
		short m_Mass;
	};
}