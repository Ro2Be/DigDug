#include "pch.h"
#include "DieStateComponent.h"
#include "GameObject.h"
#include "Game.h"
#include <iostream>
#include "HealthDisplayComponent.h"
namespace Character
{
	using namespace std;
	DieStateComponent::DieStateComponent(e::Animation* pAnimation) :
		m_pAnimation{ pAnimation }
	{
	}
	void DieStateComponent::WakeUp(const e::GameObject* /*pGameObject*/)
	{
		m_EventNotifier.AddObserver(HealthDisplayComponent::pHealthDisplayComponent);
	}
	void DieStateComponent::Update(const e::GameObject* pGameObject)
	{
		m_Timer -= e::Game::dt;
		if (m_Timer <= 0)
		{
			m_EventNotifier.Notify(new DeathEvent(pGameObject));
		}
	}
	void DieStateComponent::Launch(const e::GameObject* pGameObject)
	{
		e::AnimatorComponent* animatorComponent = pGameObject->GetpComponent<e::AnimatorComponent>("Make sure each DieStateComponent  has a AnimatorComponent sibling!");
		animatorComponent->SetAnimation(m_pAnimation);
		m_Timer = animatorComponent->GetpAnimation()->frames.size() * animatorComponent->GetpAnimation()->msPerFrame;
	}
	void DieStateComponent::Finish(const e::GameObject* /*pGameObject*/)
	{
	}
}
