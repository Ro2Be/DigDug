#include "pch.h"
#include "DefaultStateComponent.h"
#include "GameObject.h"
#include "AnimatorComponent.h"
#include "DieStateComponent.h"

namespace Character
{
	using namespace std;

	void DefaultStateComponent::WakeUp(const e::GameObject* pParent)
	{
		m_pColliderComponent = pParent->GetpComponent<e::ColliderComponent>("Make sure each DefaultStateComponent has a TransformComponent sibling!");
		pParent->GetpComponent<e::TransformComponent>("Make sure each DefaultStateComponent has a TransformComponent sibling!");
		pParent->GetpComponent<e::AnimatorComponent>("Make sure each DefaultStateComponent has a AnimatorComponent sibling!")->SetAnimation(0);
	}
	void DefaultStateComponent::Update(const e::GameObject*)
	{
		m_pColliderComponent->HandleCollision(this, "Enemy");
	}
	void DefaultStateComponent::Launch(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<e::TransformComponent>()->isActive = true;
	}
	void DefaultStateComponent::Finish(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<e::TransformComponent>()->isActive = false;
	}
	void DefaultStateComponent::HandleCollision(const e::GameObject* pGameObject, const e::GameObject* /*pOther*/) //ENEMY COLLISION HANDLER
	{
		ChangeState(pGameObject, 
			pGameObject->GetpComponent<DieStateComponent>("Make sure each Character::DefaultStateComponent has a Character::DieStateComponent sibling!"));
	}
}
