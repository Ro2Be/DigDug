#pragma once
#include "Component.h"
#include "GameObject.h"

namespace e
{
	class StateComponent abstract : public Component
	{
	public:
		StateComponent(){ isActive = false; }
		virtual ~StateComponent() override = default;
		virtual void WakeUp(const GameObject*) override = 0;
		virtual void Update(const GameObject*) override = 0;
		void ChangeState(const e::GameObject* pGameObject, StateComponent* pStateComponent)
		{
			Finish(pGameObject);
			this->isActive = false;
			pStateComponent->isActive = true;
			pStateComponent->Launch(pGameObject);
		}
	protected:
		virtual void Launch(const e::GameObject* pGameObject) = 0;
		virtual void Finish(const e::GameObject* pGameObject) = 0;
	};
}