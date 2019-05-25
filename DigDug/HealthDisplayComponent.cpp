#include "pch.h"
#include "HealthDisplayComponent.h"
#include "Event.h"
#include "TaizoHoriComponent.h"
#include <iostream>
#include "DieStateComponent.h"
using namespace std;

HealthDisplayComponent* HealthDisplayComponent::pHealthDisplayComponent{ nullptr };

void HealthDisplayComponent::WakeUp(const e::GameObject*)
{
	
}
void HealthDisplayComponent::Update(const e::GameObject*)
{
}
void HealthDisplayComponent::Observe(const e::Event* pEvent)
{
	if (const Character::DeathEvent* pDeathEvent = dynamic_cast<const Character::DeathEvent*>(pEvent))
	{
		if (pDeathEvent->pGameObject->GetpComponent<TaizoHoriComponent>()) cout << "Taizo Died";
	}
}