#pragma once
#include <Component.h>
#include "Command.h"
#include "ColliderComponent.h"
class FygarComponent final : public e::Component, e::CollisionHandler
{
public:
	FygarComponent() = default;
	virtual ~FygarComponent() override = default;
	virtual void WakeUp(const e::GameObject*) override;
	virtual void Update(const e::GameObject*) override;
	virtual void HandleCollision(const e::GameObject* pGameObject, const e::GameObject* pOtherGameObject) override;
private:
	const short speed{ 25 };
	e::Command*	m_CommandMoveLeft;
	e::Command*	m_CommandMoveDown;
	e::Command*	m_CommandMoveRight;
	e::Command*	m_CommandMoveUp;
};
