#include "pch.h"
#include "GameObject.h"
#include "TaizoHoriComponent.h"
#include "DieStateComponent.h"
using namespace std;

void TaizoHoriComponent::WakeUp(const e::GameObject* pGameObject)
{
	m_pColliderComponent = pGameObject->GetpComponent<e::ColliderComponent>("Make sure each DefaultStateComponent has a TransformComponent sibling!");
}
void TaizoHoriComponent::Update(const e::GameObject* /*pGameObject*/)
{
	m_pColliderComponent->HandleCollision(this, "Enemy");
}
void TaizoHoriComponent::HandleCollision(const e::GameObject* pGameObject, const e::GameObject* /*pOther*/) //ENEMY COLLISION HANDLER
{
	e::StateComponent* pStateComponent{ pGameObject->GetpActiveComponent<e::StateComponent>("No active state found!") };
	Character::DieStateComponent* pDieStateComponent{ pGameObject->GetpComponent<Character::DieStateComponent>("Make sure each TaizoHoriComponent has a Character::DieStateComponent sibling!") };
	if (pStateComponent != pDieStateComponent) pStateComponent->ChangeState(pGameObject, pDieStateComponent);
}