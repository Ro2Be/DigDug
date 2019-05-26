#include "pch.h"
#include "AttackStateComponent.h"
#include <utility>
#include "WeaponComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
namespace Character
{
	using namespace std;

	AttackStateComponent::AttackStateComponent(string pWeaponGameObjectName) :
		m_pWeaponName{ std::move(pWeaponGameObjectName) }
	{
	}
	void AttackStateComponent::WakeUp(const e::GameObject* pGameObject)
	{
		e::SceneManager::GetInstance().GetspActiveScene()->GetGameObject(m_pWeaponName)->GetpComponent<e::TransformComponent>()->pParent = pGameObject->GetpComponent<e::TransformComponent>();
	}
	void AttackStateComponent::Update(const e::GameObject*)
	{
	}
	void AttackStateComponent::Launch(const e::GameObject* pGameObject)
	{
		e::SceneManager::GetInstance().GetspActiveScene()->GetGameObject(m_pWeaponName)->GetpComponent<WeaponComponent>()->Fire(pGameObject);
	}
	void AttackStateComponent::Finish(const e::GameObject*)
	{

	}
}