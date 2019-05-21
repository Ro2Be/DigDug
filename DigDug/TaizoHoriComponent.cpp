#include "pch.h"
#include "GameObject.h"
#include "TaizoHoriComponent.h"
#include <iostream>

using namespace std;

void TaizoHoriCollisionHandler::HandleCollision(const e::GameObject*)
{
	cout << "COLLISION\n";
}

TaizoHoriComponent::TaizoHoriComponent() :
	m_pCollisionHandler{ new TaizoHoriCollisionHandler() }
{
}
TaizoHoriComponent::~TaizoHoriComponent()
{
	delete m_pCollisionHandler;
}
void TaizoHoriComponent::WakeUp(const e::GameObject* pParent)
{
	if (e::ColliderComponent* pColliderComponent = pParent->GetpComponent<e::ColliderComponent>())
	{
		m_pColliderComponent = pColliderComponent;
	}
	else throw runtime_error("Make sure each TaizoHoriComponent has a TransformComponent sibling!");
}
void TaizoHoriComponent::Update(const e::GameObject*)
{
	m_pColliderComponent->HandleCollision("Enemy", m_pCollisionHandler);
}