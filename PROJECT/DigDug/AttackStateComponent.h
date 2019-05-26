#pragma once
#include <StateComponent.h>
#include "Command.h"
#include "GameObject.h"

namespace Character
{
	class AttackStateComponent final : public e::StateComponent
	{
	public:
		explicit AttackStateComponent(std::string pWeaponGameObjectName);
		virtual ~AttackStateComponent() override = default;
		virtual void WakeUp(const e::GameObject*) override;
		virtual void Update(const e::GameObject*) override;
	protected:
		virtual void Launch(const e::GameObject* pGameObject) override;
		virtual void Finish(const e::GameObject* pGameObject) override;
	private:
		std::string m_pWeaponName;
	};

	//COMMANDS
	class AttackCommand final : public e::Command
	{
	public:
		AttackCommand(e::GameObject* pGameObject) :
			m_pGameObject{ pGameObject }
		{}
		virtual void Execute() override
		{
			m_pGameObject->GetpActiveComponent<e::StateComponent>("No active StateComponent found!")->ChangeState(m_pGameObject, m_pGameObject->GetpComponent<AttackStateComponent>());
		}
	private:
		e::GameObject* m_pGameObject;
	};
}
