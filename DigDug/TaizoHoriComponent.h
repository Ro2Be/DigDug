#pragma once
#include <Component.h>
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "Command.h"
#include "ColliderComponent.h"

class TaizoHoriCollisionHandler final : public e::CollisionHandler
{
public:
	~TaizoHoriCollisionHandler() override = default;
	void HandleCollision(const e::GameObject* pOtherGameObject) override;
};

class TaizoHoriComponent final : public e::Component
{
public:
	//FUNCTIONS
	TaizoHoriComponent();
	~TaizoHoriComponent() override;
	virtual void WakeUp(const e::GameObject* pParent) override;
	void Update(const e::GameObject* parent) override;
private:
	//VARIABLES
	TaizoHoriCollisionHandler* m_pCollisionHandler;
	e::ColliderComponent* m_pColliderComponent;
};
