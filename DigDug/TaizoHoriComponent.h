#pragma once
#include <Component.h>
#include "Event.h"
#include "AnimatorComponent.h"
#include "ColliderComponent.h"
//COMPONENT

class TaizoHoriComponent final : public e::Component, public e::CollisionHandler
{
public:
	//FUNCTIONS
	TaizoHoriComponent() = default;
	virtual ~TaizoHoriComponent() override = default;
	virtual void WakeUp(const e::GameObject* pGameObject) override;
	virtual void Update(const e::GameObject* pGameObject) override;
	virtual void HandleCollision(const e::GameObject* pGameObject, const e::GameObject* pOther) override;
private:
	//VARIABLES
	e::EventNotifier m_Notifier;
	e::ColliderComponent* m_pColliderComponent;
};

//EVENTS
struct DeathEvent final : public e::Event{};