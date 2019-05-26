#include "pch.h"
#include "HealthDisplayComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "TaizoHoriComponent.h"
#include <iostream>
#include "DieStateComponent.h"
#include "DefaultStateComponent.h"
using namespace std;

HealthDisplayComponent* HealthDisplayComponent::pHealthDisplayComponent{ nullptr };
HealthDisplayComponent::HealthDisplayComponent() :
	m_Lives{ 3 }
{
	pHealthDisplayComponent = this;
}
void HealthDisplayComponent::WakeUp(const e::GameObject* pGameObject)
{
	m_pTileMapComponent = pGameObject->GetpComponent<e::TileMapComponent<1, 5>>("Tilemap missing");
}
void HealthDisplayComponent::Update(const e::GameObject*)
{
}
void HealthDisplayComponent::Observe(const e::Event* pEvent)
{
	if (const Character::DeathEvent* pDeathEvent = dynamic_cast<const Character::DeathEvent*>(pEvent))
	{
		const e::GameObject* pGameObject{ pDeathEvent->pGameObject };
		if (pGameObject->GetpComponent<TaizoHoriComponent>())
		{
			LoseLive();
			pGameObject->GetpComponent<e::TransformComponent>()->position = { 120, 120 };
			pGameObject->GetpActiveComponent<e::StateComponent>("No active state found!")->ChangeState(pGameObject, pGameObject->GetpComponent<Character::DefaultStateComponent>());
		}
	}
}
void HealthDisplayComponent::GainLive()
{
	m_pTileMapComponent->SetTile(0, m_Lives, 1);
	++m_Lives;
}
void HealthDisplayComponent::LoseLive()
{
	if (m_Lives == 0)
	{
		cout << "-GAME OVER-";
		return;
	}
	--m_Lives;
	m_pTileMapComponent->SetTile(0, m_Lives, 0);
}