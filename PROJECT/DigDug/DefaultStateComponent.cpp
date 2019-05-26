#include "pch.h"
#include "DefaultStateComponent.h"
#include "GameObject.h"
#include "AnimatorComponent.h"
#include "DieStateComponent.h"

namespace Character
{
	using namespace std;
	DefaultStateComponent::DefaultStateComponent(e::Animation* pAnimation) :
		m_pAnimation{ pAnimation }
	{
		isActive = true;
	};
	void DefaultStateComponent::WakeUp(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<e::TransformComponent>("Make sure each DefaultStateComponent has a TransformComponent sibling!");
		pGameObject->GetpComponent<e::AnimatorComponent>("Make sure each DefaultStateComponent has a AnimatorComponent sibling!")->SetAnimation(m_pAnimation);
	}
	void DefaultStateComponent::Update(const e::GameObject*)
	{
	}
	void DefaultStateComponent::Launch(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<e::TransformComponent>()->isActive = true;
		pGameObject->GetpComponent<e::AnimatorComponent>("Make sure each DefaultStateComponent has a AnimatorComponent sibling!")->SetAnimation(m_pAnimation);
	}
	void DefaultStateComponent::Finish(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<e::TransformComponent>()->isActive = false;
	}
}
