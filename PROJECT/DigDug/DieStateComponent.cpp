#include "pch.h"
#include "DieStateComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "HealthDisplayComponent.h"

namespace Character
{
	using namespace std;
	DieStateComponent::DieStateComponent(e::Animation* pAnimation) :
		m_pAnimation{ pAnimation }
	{
	}
	void DieStateComponent::WakeUp(const e::GameObject* pGameObject)
	{
		m_pAnimatorComponent = pGameObject->GetpComponent<e::AnimatorComponent>("Make sure each DieStateComponent  has a AnimatorComponent sibling!");
		m_EventNotifier.AddObserver(HealthDisplayComponent::pHealthDisplayComponent);
	}
	void DieStateComponent::Update(const e::GameObject* pGameObject)
	{
		if (m_pAnimatorComponent->GetEndOfAnimation())
		{
			m_EventNotifier.Notify(new DeathEvent(pGameObject));
			//TODO RESTART LEVEL
		}
	}
	void DieStateComponent::Launch(const e::GameObject* /*pGameObject*/)
	{
		m_pAnimatorComponent->SetAnimation(m_pAnimation, false);
		m_pAnimatorComponent->SetLock(true);
	}
	void DieStateComponent::Finish(const e::GameObject* /*pGameObject*/)
	{
		m_pAnimatorComponent->SetLock(false);
	}
}
