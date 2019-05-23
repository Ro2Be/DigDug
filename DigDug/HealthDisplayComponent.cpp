#include "pch.h"
#include "HealthDisplayComponent.h"
#include "Event.h"
#include "TaizoHoriComponent.h"
#include <iostream>

void HealthDisplayComponent::WakeUp(const e::GameObject*)
{
}
void HealthDisplayComponent::Update(const e::GameObject*)
{
}
void HealthDisplayComponent::Observe(const e::Event& event)
{
	if (dynamic_cast<const DeathEvent*>(&event))
	{
		std::cout << "Loose a life\n";
	}
}
