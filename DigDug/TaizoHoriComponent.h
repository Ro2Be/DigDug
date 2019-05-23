#pragma once
#include <Component.h>
#include "Event.h"
#include "ColliderComponent.h"
#include "StateComponent.h"
//COMPONENT

class TaizoHoriComponent final : public e::Component
{
public:
	//FUNCTIONS
	TaizoHoriComponent() = default;
	~TaizoHoriComponent() override = default;
	virtual void WakeUp(const e::GameObject* pParent) override;
	virtual void Update(const e::GameObject*) override;
private:
	//VARIABLES
	e::EventNotifier m_Notifier;
};

//EVENTS
struct DeathEvent final : public e::Event{};