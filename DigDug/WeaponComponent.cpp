#include "pch.h"
#include "WeaponComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "AnimatorComponent.h"
WeaponComponent::WeaponComponent()
{
}
WeaponComponent::~WeaponComponent()
{
}
void WeaponComponent::Fire()
{
	m_pGameObject->GetpComponent<e::TextureComponent>()->isActive = true;
	m_pGameObject->GetpComponent<e::AnimatorComponent>()->SetFrame(0);
}
void WeaponComponent::WakeUp(const e::GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
	m_pGameObject->GetpComponent<e::TextureComponent>()->isActive = false;
}
void WeaponComponent::Update(const e::GameObject* pGameObject)
{

}
