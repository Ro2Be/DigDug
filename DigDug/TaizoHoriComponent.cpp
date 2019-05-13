#include "pch.h"
#include "TaizoHoriComponent.h"
#include "GameObject.h"

using namespace std;

void TaizoHoriComponent::WakeUp(const e::GameObject* pParent)
{
	if (e::TransformComponent* pTransformComponent = pParent->GetpComponent<e::TransformComponent>())
	{
		m_pTransformComponent = pTransformComponent;
	}
	else throw runtime_error("Make sure each TaizoHoriComponent has a TransformComponent sibling!");
}