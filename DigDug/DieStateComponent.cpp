#include "pch.h"
#include "DieStateComponent.h"
#include "GameObject.h"
#include "Game.h"
#include <iostream>

namespace Character
{
	using namespace std;

	void DieStateComponent::WakeUp(const e::GameObject* pGameObject)
	{

	}
	void DieStateComponent::Update(const e::GameObject* pGameObject)
	{
		m_Timer -= e::Game::dt;
		if (m_Timer <= 0)
		{
			cout << "DEAD";
		}
	}
	void DieStateComponent::Launch(const e::GameObject* pGameObject)
	{
		e::AnimatorComponent* animatorComponent = pGameObject->GetpComponent<e::AnimatorComponent>("Make sure each DieStateComponent  has a AnimatorComponent sibling!");
		animatorComponent->SetAnimation(1);
		m_Timer = animatorComponent->GetpAnimation()->frames.size() * animatorComponent->GetpAnimation()->msPerFrame;
	}
	void DieStateComponent::Finish(const e::GameObject* pGameObject)
	{
	}
}