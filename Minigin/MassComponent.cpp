#include "MiniginPCH.h"
#include "MassComponent.h"

namespace e
{
	using namespace std;
	MassComponent::MassComponent(short mass) :
		m_Mass{ mass }
	{
	}
	void MassComponent::WakeUp(const GameObject * pParent)
	{
		if (pParent->GetpComponent<BodyComponent>()) throw runtime_error(string("Make sure each MassComponent has a BodyComponent sibling!"));
	}
}