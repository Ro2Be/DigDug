#include "pch.h"
#include "WeaponComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
#include "AttackStateComponent.h"
#include "DefaultStateComponent.h"

WeaponComponent::WeaponComponent()
{
}
WeaponComponent::~WeaponComponent()
{
}
void WeaponComponent::Fire(const e::GameObject* pUser)
{
	m_pGameObject->GetpComponent<e::TextureComponent>()->isActive = true;
	m_pGameObject->GetpComponent<e::AnimatorComponent>()->SetFrame(0, false);
	m_pUser = pUser;
}
void WeaponComponent::WakeUp(const e::GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
	m_pGameObject->GetpComponent<e::TextureComponent>()->isActive = false;
}
void WeaponComponent::Update(const e::GameObject* /*pGameObject*/)
{
	if (m_pGameObject->GetpComponent<e::AnimatorComponent>()->GetEndOfAnimation())
	{
		if (m_pUser) m_pUser->GetpActiveComponent<e::StateComponent>("No active state found!")->ChangeState(m_pUser, m_pUser->GetpComponent<Character::DefaultStateComponent>());
		m_pGameObject->GetpComponent<e::TextureComponent>()->isActive = false;
	}
}